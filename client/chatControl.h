#ifndef CHATCONTROL_H
#define CHATCONTROL_H

#include <QQmlContext>
#include <QObject>
#include "chat.h"

class ChatControl : public QObject
{
    Q_OBJECT
public:
    const int RECONNECT_IN_MSEC = 1000;
    explicit ChatControl(QObject * parent = nullptr);

    /**
     * store nicname and connect to chat server
    */
    Q_INVOKABLE void connectToChat(QString nicname);

    /**
     * send message to server
    */
    Q_INVOKABLE void send(QString msg);
public slots:

    /**
     * message from server received
    */
    void onChatMessageReceived(QString msgSender, QString msg);

    /**
     * chat server connected
    */
    void onConnected();

    /**
     * chat server disconnected
    */
    void onDisconnected();

    /**
     * reconnect to server
    */
    void doReconnect();

signals:

    /**
     * invoked when we are connected to the server
    */
    void connected();

    /**
     * connection to server lost, attempt to reconnect
    */
    void reconnecting();

    /**
     * error message for login screen
     */
    void nicError(QString msg);

    /**
     * sending data from server to qml
    */
    void messageReceived(QString msgSender, QString msg);

private:
    Chat chat;
    QString nicname = "";
};

#endif // CHATCONTROL_H
