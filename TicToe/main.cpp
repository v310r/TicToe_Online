#include "mainwindow.h"
#include "QImage"
#include <QApplication>
#include <QPainter>
#include <QPaintEvent>

#include <QPushButton>
#include <QPixmap>
#include <QLabel>
#include <QHBoxLayout>
#include <QDir>

#include "TicToe.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(900,900);
    w.setWindowTitle("TicToe");

    w.show();
    return a.exec();
}
