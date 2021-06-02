#include "messages.h"
#include "message.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

Messages::Messages() {
//    add(Message("nic", "nic said something 1"));
//    add(Message("notnic", "reply to nic"));
}

QString Messages::getAllAsJson() {
    QJsonDocument result;
    QJsonArray jsonArray;
    for(auto item : items) {
        jsonArray.push_back(item.toJsonObject());
    }
    result.setArray(jsonArray);
    return QString(result.toJson());
}

void Messages::add(Message message) {
    items.push_back(message);
}

