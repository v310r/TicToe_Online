#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);

    connect(socket,&QTcpSocket::readyRead,this, &MainWindow::socketReady);
    connect(socket,&QTcpSocket::disconnected,this, &MainWindow::socketDisconnect);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    socket->connectToHost("127.0.0.1",5555);
}

void MainWindow::socketDisconnect(){
    socket->deleteLater();
}

void MainWindow::socketReady(){
    if(socket->waitForConnected(500)){
        socket->waitForReadyRead(500);
        data = socket->readAll();
        qDebug() << data;
    }
}
