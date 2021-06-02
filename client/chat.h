#ifndef CHAT_H
#define CHAT_H

#include <QString>
#include <QTcpSocket>
#include <QtNetwork>

QT_REQUIRE_CONFIG(ssl);

#include <QObject>
#include <iostream>
#include "../server/message.h"

class Chat : public QObject{
    Q_OBJECT
public:
    Chat();
    /**
     * connect to chat server via ssl
    */
    void connectToServer();

    /**
     * send message to server
    */
    void send(QString nicname, QString msg);
public slots:
    /**
     * we are connected to the server and ready to send messages
    */
    void ready();
    /**
     * incoming message received from server
    */
    void incomingMessage();
    /**
     * socket error occured
    */
    void error(QAbstractSocket::SocketError);
    /**
     * ssl error which can occur during negotiation,
     * will definitely occur for self-signed certificate
     * can be ignored in our case
    */
    void sslErrors(const QList<QSslError> &errors);

    /**
     * socket state change handeling
     * disconnect handeling implemented here
    */
    void socketStateChanged(QAbstractSocket::SocketState state);

signals:
    /**
     * message from server
    */
    void messageReceived(QString msgSender, QString msg);
    /**
     * we are connected to the server, see slot ready
    */
    void connected();
    /**
     * we are disconnected from teh server, see slot socketStateChanged
    */
    void disconnected();
private:
    QSslSocket * socket = nullptr;
};

#endif // CHAT_H
