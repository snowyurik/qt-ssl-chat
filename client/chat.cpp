#include "chat.h"
#include "chatControl.h"

Chat::Chat() {
}

void Chat::send(QString nicname, QString msg) {
    if(socket == nullptr) {
        connectToServer();
    }
    qDebug()<<"sending msg "<<msg;
    Message message(nicname, msg);
    socket->write(message.toJsonString().toStdString().c_str());
}

void Chat::connectToServer() {
    qDebug() << "connectToServer";

    socket = new QSslSocket(this);
    connect(socket, &QSslSocket::encrypted,
                this, &Chat::ready);
    connect(socket, &QSslSocket::errorOccurred,
                this, &Chat::error);
    connect(socket, QOverload<const QList<QSslError> &>::of(&QSslSocket::sslErrors),
                this, &Chat::sslErrors);
    connect(socket, &QSslSocket::stateChanged,
                this, &Chat::socketStateChanged);
    connect(socket, &QSslSocket::readyRead, this, &Chat::incomingMessage);
    socket->connectToHostEncrypted("127.0.0.1", 1234); //@todo magic
}

void Chat::ready() {
    emit connected();
}

void Chat::socketStateChanged(QAbstractSocket::SocketState state) {
    qDebug()<<"socket state changed "<<state<<"\n";
    if(state == QAbstractSocket::UnconnectedState){
        emit disconnected();
    }
}

void Chat::incomingMessage() {
   QString jsonString = socket->readAll();
   qDebug() << jsonString;
   QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
   if( doc.isNull() ) {
       return ;
   }
   if( doc.isObject() ) {
       QJsonObject jsonObject = doc.object();
       emit messageReceived(jsonObject.value("nic").toString(), jsonObject.value("msg").toString());
   }
   if( !doc.isArray()) {
       return;
   }
   QJsonArray jsonArray = doc.array();
   for(auto jsonValueRef : jsonArray) {
       QJsonObject jsonObject = jsonValueRef.toObject();
       emit messageReceived(jsonObject.value("nic").toString(), jsonObject.value("msg").toString());
   }
}

void Chat::error(QAbstractSocket::SocketError) {
    qDebug()<<"socket error";
}
void Chat::sslErrors(const QList<QSslError> &errors) {
    for(auto error : errors) {
        qDebug() << "ssl error: " << error.errorString();
    }
    qDebug()<<"proceding anyway";
    socket->ignoreSslErrors(errors);
}
