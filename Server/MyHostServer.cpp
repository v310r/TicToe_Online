#include "MyHostServer.h"
#include <iostream>

MyHostServer::MyHostServer(){}


MyHostServer::~MyHostServer(){}


void MyHostServer::startServer(){
    if(this->listen(QHostAddress::Any,5555)){
        qDebug() <<"Listening\n";
    }
    else{
        qDebug() <<"not Listening\n";
    }
}

void MyHostServer::incomingConnection(qintptr socketDescriptor){
    socket = new QTcpSocket(this);

    socket->setSocketDescriptor(socketDescriptor);

    connect(socket,&QTcpSocket::readyRead,this,&MyHostServer::socketReady);
    connect(socket,&QTcpSocket::disconnected,this,&MyHostServer::socketDisconnect);

    qDebug() <<"Descriptor "<<socketDescriptor<<" client connected\n";

    socket->write("You are connected\n");
    qDebug() <<"Sent client connect status - YES\n";
}

void MyHostServer::socketReady(){

}

void MyHostServer::socketDisconnect(){
    qDebug() <<"Disconnect\n";
    socket->deleteLater();
}
