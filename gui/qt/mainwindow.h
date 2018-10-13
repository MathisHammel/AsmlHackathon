#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QResizeEvent>


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
    void read();

    Q_SLOT void sendRequest();
    Q_SLOT void sendRequestPanels();

    Q_SLOT void onFinishPanels(QNetworkReply *rep);
    Q_SLOT void onFinish(QNetworkReply *rep);
protected:

    void resizeEvent(QResizeEvent* event);

private:

    Ui::MainWindow *ui;

    vector<vector<bool>>* m_currentModel;
    vector<vector<bool>> m_modelA;
    vector<vector<bool>> m_modelB;

    QTimer* m_refreshTimer;
};

#endif // MAINWINDOW_H
