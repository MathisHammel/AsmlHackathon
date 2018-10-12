#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <vector>

//DONT DO IT, KIDS LIKE THIS
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Q_SLOT void selectA();
    Q_SLOT void selectB();
    void saveCurrent();
    Q_SLOT void writeToPort();


private:

    Ui::MainWindow *ui;

    vector<vector<bool>>* m_currentModel;
    vector<vector<bool>> m_modelA;
    vector<vector<bool>> m_modelB;
};

#endif // MAINWINDOW_H
