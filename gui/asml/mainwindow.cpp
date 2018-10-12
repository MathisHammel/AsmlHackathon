#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->canvas->setFixedSize(QSize(500, 500));
    ui->canvas->show();
}



MainWindow::~MainWindow()
{
    delete ui;
}
