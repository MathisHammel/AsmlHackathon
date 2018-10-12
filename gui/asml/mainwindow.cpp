#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->canvas->show();

    m_modelA = ui->canvas->getModel();
    m_modelB = ui->canvas->getModel();

    connect(ui->clearButton, &QPushButton::pressed, ui->canvas, &PaletteEditor::clear);
    connect(ui->editAbutton, &QPushButton::pressed, this, &MainWindow::selectA);
    connect(ui->editBbutton, &QPushButton::pressed, this, &MainWindow::selectB);

    m_currentModel = &m_modelA;
    selectA();
}

void MainWindow::saveCurrent(){
    *m_currentModel = ui->canvas->getModel();
}

Q_SLOT void MainWindow::selectA(){
    saveCurrent();
    m_currentModel = &m_modelA;
    ui->canvas->loadModel(m_modelA);
    ui->editAbutton->setEnabled(false);
    ui->editBbutton->setEnabled(true);
    update();
}

Q_SLOT void MainWindow::selectB(){
    saveCurrent();
    m_currentModel = &m_modelB;
    ui->canvas->loadModel(m_modelB);
    ui->editBbutton->setEnabled(false);
    ui->editAbutton->setEnabled(true);

    update();
}

MainWindow::~MainWindow()
{
    delete ui;
}
