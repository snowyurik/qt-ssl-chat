#ifndef MESSAGES_H
#define MESSAGES_H

#include <QString>
#include "message.h"


class Messages
{
public:
    Messages();
    QString getAllAsJson();
    void add(Message message);
    void addFromJson(QString jsonString);
private:
    QList<Message> items;
};

#endif // MESSAGES_H
