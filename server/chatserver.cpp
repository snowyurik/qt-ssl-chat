#include "chatserver.h"

ChatServer::ChatServer(QObject *parent) :
    QTcpServer(parent) {
    setSslCertificate("server.pem");
    setSslKey("server.key");
}

void ChatServer::startServer() {
    int port = 1234;

    if(!this->listen(QHostAddress::Any, port)) {
        qDebug() << "Could not start server";
    } else {
        qDebug() << "Listening to port " << port << "...";
    }
    connect(this, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
}

void ChatServer::incomingConnection(qintptr socketDescriptor) {
    QSslSocket *socket = new QSslSocket();
    if(!socket->setSocketDescriptor(socketDescriptor)){
        delete socket;
        return;
    }
    addPendingConnection(socket);
}

void ChatServer::acceptConnection() {
    qDebug() << "acceptConnection";
    QSslSocket *socket = dynamic_cast<QSslSocket *>(nextPendingConnection());
    assert(socket);

    // QSslSocket emits the encrypted() signal after the encrypted connection is established
    connect(socket, SIGNAL(encrypted()), this, SLOT(handshakeComplete()));

    // Report any SSL errors that occur
    connect(socket, SIGNAL(sslErrors(const QList<QSslError> &)), this, SLOT(sslErrors(const QList<QSslError> &)));

//    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(connectionFailure()));

    socket->setPrivateKey(getSslKey());
    socket->setLocalCertificate(getSslCertificate());
    socket->setProtocol(getSslProtocol());
    socket->setPeerVerifyMode(QSslSocket::VerifyNone);
    qDebug() << "wait for encryption";
    socket->startServerEncryption();
}

void ChatServer::handshakeComplete() {
    qDebug() << "handshakeComplete";
    QSslSocket *socket = dynamic_cast<QSslSocket *>(sender());
    assert(socket);

    connect(socket, SIGNAL(disconnected()), this, SLOT(connectionClosed()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(receiveMessage()));

    qDebug() << "handshake complete";

    clientSockets.push_back(socket);

    socket->write(messages.getAllAsJson().toStdString().c_str());
}

void ChatServer::receiveMessage() {
    QSslSocket *socket = dynamic_cast<QSslSocket *>(sender());
    assert(socket);
    QString jsonString = socket->readAll();
    qDebug() << "from client: " << jsonString;
    Message message = Message::fromJsonString(jsonString);
    messages.add(message);
    for(auto clientSocket : clientSockets) {
        clientSocket->write(message.toJsonString().toStdString().c_str());
    }
}
void ChatServer::connectionClosed() {}
void ChatServer::connectionFailure() {}
void ChatServer::sslErrors(const QList<QSslError> &errors) {
    qDebug() << "ssl errors";
}

void ChatServer::setSslCertificate(QSslCertificate certificate) {
    this->certificate = certificate;
}

void ChatServer::setSslCertificate(QString filename, QSsl::EncodingFormat format) {
    QFile certificateFile(filename);

    if (!certificateFile.open(QIODevice::ReadOnly)) {
        throw EChatServer("can't open ssl serificate");
    }
    setSslCertificate(QSslCertificate(certificateFile.readAll(), format));
}

void ChatServer::setSslKey(QSslKey sslKey ){
    this->sslKey = sslKey;
}

void ChatServer::setSslKey(QString fileName, QSsl::KeyAlgorithm algorithm, QSsl::EncodingFormat format, const QByteArray &passPhrase) {
    QFile keyFile(fileName);
    if (!keyFile.open(QIODevice::ReadOnly)) {
        throw EChatServer("can't open ssl key file");
    }
    setSslKey(QSslKey(keyFile.readAll(), algorithm, format, QSsl::PrivateKey, passPhrase));
}

void ChatServer::setSslProtocol(QSsl::SslProtocol sslProtocol) {
    this->sslProtocol = sslProtocol;
}

QSslCertificate ChatServer::getSslCertificate() { return certificate; }
QSslKey ChatServer::getSslKey() { return sslKey; }
QSsl::SslProtocol ChatServer::getSslProtocol() { return sslProtocol; }
