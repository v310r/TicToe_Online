#ifndef MYHOSTSERVER_H
#define MYHOSTSERVER_H

#include <QTcpServer>
#include <QTcpSocket>

class MyHostServer : public QTcpServer
{
    Q_OBJECT
public:
    MyHostServer();
    ~MyHostServer();

    QTcpSocket* socket;
    QByteArray data;

public slots:
    void startServer();
    void incomingConnection(qintptr socketDescriptor)override;
    void socketReady();
    void socketDisconnect();
};


#endif // MYHOSTSERVER_H
