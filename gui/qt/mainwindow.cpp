#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../../src/shapes.hpp"

#include <QDebug>
#include <QThread>
#include <QIODevice>

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

    for (QSerialPortInfo port : QSerialPortInfo::availablePorts())
    {
        ui->portSelector->addItem(port.portName());
    }

    connect(ui->portSelector, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated), this, [this](int i){
        selectPort(ui->portSelector->itemText(i) );
    });

    ui->runButton->setEnabled(false);

    //selectPort(ui->portSelector->itemText(0));


    m_modelA = ui->canvas->getModel();
    m_modelB = ui->canvas->getModel();

    connect(ui->clearButton, &QPushButton::pressed, ui->canvas, &PaletteEditor::clear);
    connect(ui->editAbutton, &QPushButton::pressed, this, &MainWindow::selectA);
    connect(ui->editBbutton, &QPushButton::pressed, this, &MainWindow::selectB);
    connect(ui->runButton, &QPushButton::pressed, this, &MainWindow::writeToPort);

    ui->selectShape->addItem("----");
    ui->selectShape->addItem("Triangle");
    ui->selectShape->addItem("Square");
    ui->selectShape->addItem("Diamond");
    ui->selectShape->addItem("Circle");
    ui->selectShape->addItem("Large Disk");
    ui->selectShape->addItem("Small Disk");


    connect(ui->selectShape, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated), this, [this](int i){
        qDebug() << i << " selected";
        Shapes::Shape obj;
        Shapes::Type t;
        if (!i)
            return;

        switch(i){
        case 1:
            t = Shapes::TRIANGLE;
            ui->canvas->loadModel(toModel(obj.get(t,  4 , 1)));
            break;
        case 2:
            t = Shapes::SQUARE;
            ui->canvas->loadModel(toModel(obj.get(t,  4 , 32)));
            break;
        case 3:
            t = Shapes::DIAMOND;
            ui->canvas->loadModel(toModel(obj.get(t,  4 , 1)));
            break;
        case 4:
            t = Shapes::ROUND;
            ui->canvas->loadModel(toModel(obj.get(t,  4 , 1)));
            break;
        case 5:
            t = Shapes::LARGE_OPAQUE;
            ui->canvas->loadModel(toModel(obj.get(t,  4 , 1)));
            break;
        case 6:
            t = Shapes::SMALL_OPAQUE;
            ui->canvas->loadModel(toModel(obj.get(t,  4 , 1)));
            break;

        }
        //ui->canvas->loadModel(toModel(obj.get(t,  4 , 1)));
        update();
    });

    m_currentModel = &m_modelA;
    selectA();
}

void MainWindow::selectPort(const QString& portName)
{
    //if (m_serialPort && m_serialPort->isOpen())
    //    m_serialPort->close();

     qDebug() << "port name" << portName;
    m_serialPort = new QSerialPort(this);
    m_serialPort->setPortName(portName);

    const int serialPortBaudRate = QSerialPort::Baud9600;
    m_serialPort->setBaudRate(serialPortBaudRate);
    m_serialPort->setDataBits(QSerialPort::Data8);
    m_serialPort->setParity(QSerialPort::NoParity);
    m_serialPort->setStopBits(QSerialPort::OneStop);
    m_serialPort->setFlowControl(QSerialPort::NoFlowControl);


    if (!m_serialPort->open(QIODevice::ReadWrite)) {
        qDebug() << QObject::tr("Failed to open port %1, error: %2")
                          .arg(portName).arg(m_serialPort->error()) << endl;
    }

    if (m_serialPort->isOpen() && m_serialPort->isWritable())
    {
        qDebug() << "Serial is open";
    }

    m_serialPort->setDataTerminalReady(true);
    m_serialPort->setRequestToSend(true);

    ui->portSelector->setEnabled(false);
    ui->runButton->setEnabled(true);

    connect(m_serialPort, &QSerialPort::readyRead, this, &MainWindow::read);
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

void MainWindow::writeToPort(){
        const char* data = "TEST";
        const QByteArray writeData(data);

        if (writeData.isEmpty()) {
            qDebug() << QObject::tr("Either no data was currently available on "
                                          "the standard input for reading, "
                                          "or an error occurred for port %1, error: %2")
                              .arg(m_serialPort->portName()).arg(m_serialPort->errorString()) << endl;
            return;
        }

        qDebug() << "start to write";
        qDebug() << "written " << m_serialPort->write(writeData);
        m_serialPort->flush();
        qDebug() << "wait for written" << m_serialPort->waitForBytesWritten(2000);
        //qDebug() << "wait for ready read" << m_serialPort->waitForReadyRead(2000);

        //read();
}

void MainWindow::read(){

        QByteArray readData = m_serialPort->readAll();
        while (m_serialPort->waitForReadyRead(1000))
            readData.append(m_serialPort->readAll());

        if (m_serialPort->error() == QSerialPort::ReadError) {
            qDebug() << QObject::tr("Failed to read from port %1, error: %2")
                              .arg(m_serialPort->portName()).arg(m_serialPort->errorString()) << endl;
            return;
        } else if (m_serialPort->error() == QSerialPort::TimeoutError && readData.isEmpty()) {
            qDebug() << QObject::tr("No data was currently available"
                                          " for reading from port %1")
                              .arg(m_serialPort->portName()) << endl;
            return;
        }

        qDebug() << QObject::tr("Data successfully received from port %1")
                          .arg(m_serialPort->portName()) << endl;
        qDebug() << "Read" << readData << endl;
}
