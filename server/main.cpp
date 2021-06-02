#include <QCoreApplication>
#include "chatserver.h"

int main(int argc, char *argv[])
{
    int result = 1;
    QCoreApplication a(argc, argv);
    try {
        ChatServer chatServer;
        chatServer.startServer();
        result = a.exec();
    } catch(EChatServer e) {
        qDebug() << e.getMessage();
    }
    return result;
}
