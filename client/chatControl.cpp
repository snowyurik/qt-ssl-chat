#include "chatControl.h"
#include "chat.h"

ChatControl::ChatControl(QObject * parent) : QObject( parent ) {
    connect(&chat, &Chat::messageReceived, this, &ChatControl::onChatMessageReceived);
}

void ChatControl::send(QString msg) {
   qDebug() << "ChatControl.send";
   if(msg.simplified().isEmpty()) {
       return;
   }
   chat.send(nicname, msg);
}

void ChatControl::connectToChat(QString nicname) {
    qDebug() << nicname << ":" << nicname.simplified()<<":"<<nicname.simplified().isEmpty();
    if(nicname.simplified().isEmpty()) {
        emit nicError("Nicname is empty");
        return;
    }
    this->nicname = nicname.simplified();
    connect(&chat, &Chat::connected, this, &ChatControl::onConnected);
    connect(&chat, &Chat::disconnected, this, &ChatControl::onDisconnected);
    chat.connectToServer();
}

void ChatControl::onConnected() {
    emit connected();
}

void ChatControl::onDisconnected() {
    qDebug()<<"connection to server lost, reconnecting";
    emit reconnecting();
    QTimer::singleShot(ChatControl::RECONNECT_IN_MSEC, this, &ChatControl::doReconnect);
}

void ChatControl::doReconnect() {
    chat.connectToServer();
}

void ChatControl::onChatMessageReceived(QString msgSender, QString msg) {
    emit messageReceived(msgSender, msg);
}

