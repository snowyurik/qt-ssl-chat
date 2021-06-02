#include "message.h"
#include <QJsonObject>
#include <QJsonDocument>

Message::Message(QString nicname, QString msg) {
    this->nicname = nicname;
    this->msg = msg;
    this->time = QTime::currentTime();
}

QJsonObject Message::toJsonObject() {
    QJsonObject jsonObject {
     { "nic", nicname },
     { "msg", msg },
     { "time", time.toString() }
    };
    return jsonObject;
}

QString Message::toJsonString() {
    QJsonDocument result;
    result.setObject(toJsonObject());
    return  QString(result.toJson());
}

Message Message::fromJsonString(QString jsonString) {
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
    /*if( doc.isNull() ) {
        return ; // todo proper exception
    }
    if( !doc.isObject() ) {
        return ;
    }*/
    QJsonObject jsonObject = doc.object();
    return Message(jsonObject.value("nic").toString(), jsonObject.value("msg").toString());
}
