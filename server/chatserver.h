#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QTcpServer>
#include <QException>
#include <QSslSocket>
#include <QSsl>
#include <QSslCertificate>
#include <QSslKey>
#include <QFile>
#include "messages.h";

class EChatServer : public QException {
public:
//    EChatServer() {}
    EChatServer(QString msg) {
        message = msg;
    }
    void raise() const override { throw *this; }
    EChatServer *clone() const override { return new EChatServer(*this); }
    QString getMessage() { return message; }
private:
    QString message = "";
};

class ChatServer : public QTcpServer {
    Q_OBJECT
public:
    explicit ChatServer(QObject *parent = 0);
    void startServer();
    void setSslCertificate(QSslCertificate certificate);
    void setSslCertificate(QString filename, QSsl::EncodingFormat format = QSsl::Pem);
    void setSslKey(QSslKey sslKey);
    void setSslKey(QString fileName, QSsl::KeyAlgorithm algorithm = QSsl::Rsa
            , QSsl::EncodingFormat format = QSsl::Pem
            , const QByteArray &passPhrase = QByteArray());
    void setSslProtocol(QSsl::SslProtocol sslProtocol);
    QSslCertificate getSslCertificate();
    QSslKey getSslKey();
    QSsl::SslProtocol getSslProtocol();
signals:

public slots:
    void acceptConnection();
    void handshakeComplete();
    void sslErrors(const QList<QSslError> &errors);
    void receiveMessage();
    void connectionClosed();
    void connectionFailure();
protected:
    void incomingConnection(qintptr socketDescriptor);
private:
    /** pem sertificate */
    QSslCertificate certificate;
    QSslKey sslKey;
    QSsl::SslProtocol sslProtocol = QSsl::TlsV1_2;
    QList<QSslSocket *> clientSockets;
    Messages messages;
};

#endif // CHATSERVER_H
