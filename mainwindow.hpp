#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "epocthread.hpp"
#include "epocDevice.hpp"

#include <QString>
#include <QVector>

#include <QTimer>

#include <QGraphicsScene>
#include <QImage>

#include <math.h>
#include <fftw3.h>


#define GAMMA_SUP 50
#define GAMMA_INF 30
#define BETA_INF 12
#define ALPHA_INF 8
#define THETA_INF 4
#define DELTA_INF .5

namespace Ui
{
    class MainWindow ;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget * parent = 0) ;
    ~MainWindow() ;

private:
    Ui::MainWindow * ui ;

    epocDevice * device ;
    epocThread * th ;
    QTimer * timerDraw ;

    bool isCheckedAF34 ;
    bool isCheckedF34 ;
    bool isCheckedF78 ;
    bool isCheckedFC56 ;
    bool isCheckedT78 ;
    bool isCheckedP78 ;
    bool isCheckedO12 ;

    bool isConnected ;
    bool isStarted ;

    void drawSignal() ;
    void computeFFT() ;
    void drawFreq() ;

    QVector<int> vecDataAF3, vecDataAF4, vecDataF3, vecDataF4, vecDataF7, vecDataF8, vecDataFC5, vecDataFC6, vecDataT7, vecDataT8, vecDataP7, vecDataP8, vecDataO1, vecDataO2 ;
    QVector<double> vecFoufou ;

    double delta, theta, alpha, beta, gamma ;
    QGraphicsScene sceneSignal, sceneFreq ;

    QPen pen ;
    QRadialGradient radialGrad ;
    QBrush brush ;

    QVector<QPainterPath> vecPath ;



private slots:
    void slotChecked() ;
    void slotCheckedAll() ;
    void slotConnect() ;
    void slotStart() ;
    void slotDraw() ;
} ;

#endif // MAINWINDOW_HPP
