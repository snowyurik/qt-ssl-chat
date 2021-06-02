#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QTime>

class Message {
public:
    Message(QString nicname, QString msg);
    static Message fromJsonString(QString jsonString);
    QJsonObject toJsonObject();
    QString toJsonString();
private:
    QString nicname;
    QString msg;
    QTime time;
};

#endif // MESSAGE_H
