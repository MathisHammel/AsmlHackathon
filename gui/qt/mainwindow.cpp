#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../../algorithms/shapes.hpp"
#include <QDebug>

vector<vector<bool>> toModel(char** mat){

    vector<vector<bool>> res = vector<vector<bool>>(32, vector<bool>(32, false));
    for (int i = 0; i < 32; ++i){
        for (int j = 0; j < 32; ++j){
            res[i][j] = (mat[i][j] != 0);
        }
    }
    return res;
}

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

    ui->selectShape->addItem("----");
    ui->selectShape->addItem("Triangle");
    ui->selectShape->addItem("Square");
    ui->selectShape->addItem("Diamond");

    connect(ui->selectShape, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated), this, [this](int i){
        qDebug() << i << " selected";
        Shapes::Shape obj;
        Shapes::Type t;
        if (!i)
            return;

        switch(i){
        case 1:
            t = Shapes::TRIANGLE;
            break;
        case 2:
            t = Shapes::SQUARE;
            break;
        case 3:
            t = Shapes::DIAMOND;
            break;

        }
        ui->canvas->loadModel(toModel(obj.get(t,  4 , 32)));
        update();
    });

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
