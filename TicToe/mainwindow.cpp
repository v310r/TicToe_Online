#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

#include "TicToe.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(new TicToe());

}

MainWindow::~MainWindow()
{
    delete ui;
}

