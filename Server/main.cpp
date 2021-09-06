#include "mainwindow.h"

#include <QApplication>

#include "MyHostServer.h"

#include "../TicToe/TicToe.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    MyHostServer server;
    server.startServer();

    return a.exec();
}
