/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include <paletteeditor.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    PaletteEditor *canvas;
    QGridLayout *gridLayout;
    QPushButton *clearButton;
    QLabel *label_2;
    QPushButton *editAbutton;
    QPushButton *runButton;
    QComboBox *selectShape;
    QSpacerItem *verticalSpacer_2;
    QPushButton *editBbutton;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_3;
    QLabel *label_3;
    QComboBox *adjustPanels;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(787, 556);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(30, 10, 731, 521));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        canvas = new PaletteEditor(horizontalLayoutWidget);
        canvas->setObjectName(QStringLiteral("canvas"));

        horizontalLayout->addWidget(canvas);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        clearButton = new QPushButton(horizontalLayoutWidget);
        clearButton->setObjectName(QStringLiteral("clearButton"));

        gridLayout->addWidget(clearButton, 2, 0, 1, 1);

        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 6, 0, 1, 1);

        editAbutton = new QPushButton(horizontalLayoutWidget);
        editAbutton->setObjectName(QStringLiteral("editAbutton"));

        gridLayout->addWidget(editAbutton, 3, 0, 1, 1);

        runButton = new QPushButton(horizontalLayoutWidget);
        runButton->setObjectName(QStringLiteral("runButton"));

        gridLayout->addWidget(runButton, 11, 0, 1, 1);

        selectShape = new QComboBox(horizontalLayoutWidget);
        selectShape->setObjectName(QStringLiteral("selectShape"));

        gridLayout->addWidget(selectShape, 7, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 0, 0, 1, 1);

        editBbutton = new QPushButton(horizontalLayoutWidget);
        editBbutton->setObjectName(QStringLiteral("editBbutton"));

        gridLayout->addWidget(editBbutton, 4, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 10, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 5, 0, 1, 1);

        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 8, 0, 1, 1);

        adjustPanels = new QComboBox(horizontalLayoutWidget);
        adjustPanels->setObjectName(QStringLiteral("adjustPanels"));

        gridLayout->addWidget(adjustPanels, 9, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        horizontalLayout->setStretch(0, 3);
        horizontalLayout->setStretch(1, 1);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        clearButton->setText(QApplication::translate("MainWindow", "Clear", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Predefined shape:", Q_NULLPTR));
        editAbutton->setText(QApplication::translate("MainWindow", "Edit shape A", Q_NULLPTR));
        runButton->setText(QApplication::translate("MainWindow", "Run", Q_NULLPTR));
        editBbutton->setText(QApplication::translate("MainWindow", "Edit Shape B", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Adjust for number of panels", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
