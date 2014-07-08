#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this) ;

    device = new epocDevice() ;
    th = new epocThread(device) ;
    timerDraw = new QTimer() ;
    timerDraw->setInterval(100) ;

    ui->graphSignal->setScene(&sceneSignal) ;

    QPixmap pix ;
    pix.fromImage(QImage("../epocWatch/images/head.jpg")) ;
    QGraphicsScene scenePosition ;
    ui->graphPosition->setScene(&scenePosition) ;
    scenePosition.addPixmap(pix) ;

    vecDataAF3.fill(0, 1024) ;
    vecDataAF4.fill(0, 1024) ;
    vecDataF3.fill(0, 1024) ;
    vecDataF4.fill(0, 1024) ;
    vecDataF7.fill(0, 1024) ;
    vecDataF8.fill(0, 1024) ;
    vecDataFC5.fill(0, 1024) ;
    vecDataFC6.fill(0, 1024) ;
    vecDataT7.fill(0, 1024) ;
    vecDataT8.fill(0, 1024) ;
    vecDataP7.fill(0, 1024) ;
    vecDataP8.fill(0, 1024) ;
    vecDataO1.fill(0, 1024) ;
    vecDataO2.fill(0, 1024) ;

    vecFoufou.fill(0, 1024) ;

    isCheckedAF34 = false ;
    isCheckedF34 = false ;
    isCheckedF78 = false ;
    isCheckedFC56 = false ;
    isCheckedO12 = false ;
    isCheckedP78 = false ;
    isCheckedT78 = false ;

    ui->progressDelta->setStyleSheet(ui->progressDelta->property("defaultStyleSheet").toString() +
                                       " QProgressBar::chunk { background: yellow; }") ;
    ui->progressTheta->setStyleSheet(ui->progressTheta->property("defaultStyleSheet").toString() +
                                       " QProgressBar::chunk { background: orange; }") ;
    ui->progressAlpha->setStyleSheet(ui->progressAlpha->property("defaultStyleSheet").toString() +
                                       " QProgressBar::chunk { background: blue; }") ;
    ui->progressBeta->setStyleSheet(ui->progressBeta->property("defaultStyleSheet").toString() +
                                       " QProgressBar::chunk { background: green; }") ;
    ui->progressGamma->setStyleSheet(ui->progressGamma->property("defaultStyleSheet").toString() +
                                       " QProgressBar::chunk { background: red; }") ;


    connect(ui->cbAF34, SIGNAL(clicked()), this, SLOT(slotChecked())) ;
    connect(ui->cbF34, SIGNAL(clicked()), this, SLOT(slotChecked())) ;
    connect(ui->cbF78, SIGNAL(clicked()), this, SLOT(slotChecked())) ;
    connect(ui->cbFC56, SIGNAL(clicked()), this, SLOT(slotChecked())) ;
    connect(ui->cbO12, SIGNAL(clicked()), this, SLOT(slotChecked())) ;
    connect(ui->cbP78, SIGNAL(clicked()), this, SLOT(slotChecked())) ;
    connect(ui->cbT78, SIGNAL(clicked()), this, SLOT(slotChecked())) ;
    connect(ui->cbAll, SIGNAL(clicked()), this, SLOT(slotCheckedAll())) ;

    connect(timerDraw, SIGNAL(timeout()), this, SLOT(slotDraw())) ;

    connect(ui->pbConnect, SIGNAL(clicked()), this, SLOT(slotConnect())) ;
    connect(ui->pbStart, SIGNAL(clicked()), this, SLOT(slotStart())) ;
    connect(ui->pbQuit, SIGNAL(clicked()), this, SLOT(close())) ;
}

MainWindow::~MainWindow()
{
    delete device ;
    delete ui;
}

// SLOTS

void MainWindow::slotChecked()
{
    if (ui->cbAll->isChecked())
    {
        ui->cbAll->setChecked(false) ;
    }
    isCheckedAF34 = ui->cbAF34->isChecked() ;
    isCheckedF34 = ui->cbF34->isChecked() ;
    isCheckedF78 = ui->cbF78->isChecked() ;
    isCheckedFC56 = ui->cbFC56->isChecked() ;
    isCheckedO12 = ui->cbO12->isChecked() ;
    isCheckedP78 = ui->cbP78->isChecked() ;
    isCheckedT78 = ui->cbT78->isChecked() ;

    if (isCheckedAF34 && isCheckedF34 && isCheckedF78 && isCheckedFC56 && isCheckedO12 && isCheckedP78 && isCheckedT78)
        ui->cbAll->setChecked(true) ;
}

void MainWindow::slotCheckedAll()
{
    if (ui->cbAll->isChecked())
    {
        ui->cbAF34->setChecked(true) ;
        isCheckedAF34 =  true ;
        ui->cbF34->setChecked(true) ;
        isCheckedF34 =  true ;
        ui->cbF78->setChecked(true) ;
        isCheckedF78 =  true ;
        ui->cbFC56->setChecked(true) ;
        isCheckedFC56 =  true ;
        ui->cbO12->setChecked(true) ;
        isCheckedO12 =  true ;
        ui->cbP78->setChecked(true) ;
        isCheckedP78 =  true ;
        ui->cbT78->setChecked(true) ;
        isCheckedT78 =  true ;
    }
    else
    {
        ui->cbAF34->setChecked(false) ;
        isCheckedAF34 =  false ;
        ui->cbF34->setChecked(false) ;
        isCheckedF34 =  false ;
        ui->cbF78->setChecked(false) ;
        isCheckedF78 =  false ;
        ui->cbFC56->setChecked(false) ;
        isCheckedFC56 =  false ;
        ui->cbO12->setChecked(false) ;
        isCheckedO12 =  false ;
        ui->cbP78->setChecked(false) ;
        isCheckedP78 =  false ;
        ui->cbT78->setChecked(false) ;
        isCheckedT78 =  false ;
    }
}

void MainWindow::slotConnect()
{
    if (isConnected == false)
        isConnected = (device->connect() == 0) ;
    else
    {
        isConnected = false ;
        isStarted = false ;
        device->disconnect() ;
        ui->pbConnect->setText("CONNECT") ;
        ui->statusBar->showMessage("is disconnecting", 2000) ;
        th->terminate() ;
        th->quit() ;
    }

    if (isConnected == true)
    {
        ui->pbConnect->setText("DISCONNECT") ;
        ui->statusBar->showMessage("is connecting", 2000) ;
        th->start() ;
    }
}

void MainWindow::slotStart()
{
    if (isConnected == true)
    {
        isStarted = !isStarted ;

        if (isStarted == true)
        {
            ui->pbStart->setText("STOP") ;
            ui->statusBar->showMessage("is starting", 2000) ;
            timerDraw->start() ;
        }
        else
        {
            ui->pbStart->setText("START") ;
            ui->statusBar->showMessage("is stopping", 2000) ;
            timerDraw->stop() ;
        }
    }
}

void MainWindow::slotDraw()
{
    QVector<int> v(th->getCounter()) ;
    std::cout << v.size() << std::endl ;
    for (int i = 0 ; i < v.size() ; i++)
        std::cout << "\t" << v.at(i) << std::endl ;

    drawSignal() ;

    computeFFT() ;

    drawFreq() ;

}


void MainWindow::drawSignal()
{
    sceneSignal.clear() ;

    QImage img(vecDataAF3.size(), ui->graphSignal->height(), QImage::Format_ARGB32) ;
    img.fill(qRgba(0, 0, 0, 0)) ;
    int midY = ui->graphSignal->height()/2 ;

    vecFoufou.fill(0, 1024) ;

    if (isCheckedAF34)
    {
        QVector<int> vecData ;
        QVector<int> c1(th->getAF3()) ;
        QVector<int> c2(th->getAF4()) ;
        vecDataAF3 << c1 ;
        vecDataAF3.erase(vecDataAF3.begin(), vecDataAF3.begin() + c1.size()) ;
        vecDataAF4 << c2 ;
        vecDataAF4.erase(vecDataAF4.begin(), vecDataAF4.begin() + c2.size()) ;

        for (int k = 0 ; k < vecDataAF3.size() ; k++)
        {
            vecData.push_back((vecDataAF3.at(k) + vecDataAF4.at(k))/20 - 900) ;
            vecFoufou.replace(k, vecFoufou.at(k) + vecDataAF3.at(k) + vecDataAF4.at(k)) ;
        }
        for (int i = 0 ; i < vecData.size() ; i++)
        {
            img.setPixel(i, midY - vecData[i], qRgb(255, 0, 0)) ;
        }
    }

    if (isCheckedF34)
    {
        QVector<int> vecData ;
        QVector<int> c1(th->getF3()) ;
        QVector<int> c2(th->getF4()) ;
        vecDataF3 << c1 ;
        vecDataF3.erase(vecDataF3.begin(), vecDataF3.begin() + c1.size()) ;
        vecDataF4 << c2 ;
        vecDataF4.erase(vecDataF4.begin(), vecDataF4.begin() + c2.size()) ;

        for (int k = 0 ; k < vecDataF3.size() ; k++)
        {
            vecData.push_back((vecDataF3.at(k) + vecDataF4.at(k))/20 - 900) ;
            vecFoufou.replace(k, vecFoufou.at(k) + vecDataF3.at(k) + vecDataF4.at(k)) ;
        }
        for (int i = 0 ; i < vecData.size() ; i++)
        {
            img.setPixel(i, midY - vecData[i], qRgb(255, 80, 0)) ;
        }

    }

    if (isCheckedF78)
    {
        QVector<int> vecData ;
        QVector<int> c1(th->getF7()) ;
        QVector<int> c2(th->getF8()) ;
        vecDataF7 << c1 ;
        vecDataF7.erase(vecDataF7.begin(), vecDataF7.begin() + c1.size()) ;
        vecDataF8 << c2 ;
        vecDataF8.erase(vecDataF8.begin(), vecDataF8.begin() + c2.size()) ;

        for (int k = 0 ; k < vecDataF7.size() ; k++)
        {
            vecData.push_back((vecDataF7.at(k) + vecDataF8.at(k))/20 - 900) ;
            vecFoufou.replace(k, vecFoufou.at(k) + vecDataF7.at(k) + vecDataF8.at(k)) ;
        }
        for (int i = 0 ; i < vecData.size() ; i++)
        {
            img.setPixel(i, midY - vecData[i], qRgb(255, 255, 0)) ;
        }
    }

    if (isCheckedFC56)
    {
        QVector<int> vecData ;
        QVector<int> c1(th->getFC5()) ;
        QVector<int> c2(th->getFC6()) ;
        vecDataFC5 << c1 ;
        vecDataFC5.erase(vecDataFC5.begin(), vecDataFC5.begin() + c1.size()) ;
        vecDataFC6 << c2 ;
        vecDataFC6.erase(vecDataFC6.begin(), vecDataFC6.begin() + c2.size()) ;

        for (int k = 0 ; k < vecDataFC5.size() ; k++)
        {
            vecData.push_back((vecDataFC5.at(k) + vecDataFC6.at(k))/20 - 900) ;
            vecFoufou.replace(k, vecFoufou.at(k) + vecDataFC5.at(k) + vecDataFC6.at(k)) ;
        }
        for (int i = 0 ; i < vecData.size() ; i++)
        {
            img.setPixel(i, midY - vecData[i], qRgb(0, 255, 0)) ;
        }
    }

    if (isCheckedT78)
    {
        QVector<int> vecData ;
        QVector<int> c1(th->getT7()) ;
        QVector<int> c2(th->getT8()) ;
        vecDataT7 << c1 ;
        vecDataT7.erase(vecDataT7.begin(), vecDataT7.begin() + c1.size()) ;
        vecDataT8 << c2 ;
        vecDataT8.erase(vecDataT8.begin(), vecDataT8.begin() + c2.size()) ;

        for (int k = 0 ; k < vecDataT7.size() ; k++)
        {
            vecData.push_back((vecDataT7.at(k) + vecDataT8.at(k))/20 - 900) ;
            vecFoufou.replace(k, vecFoufou.at(k) + vecDataT7.at(k) + vecDataT8.at(k)) ;
        }
        for (int i = 0 ; i < vecData.size() ; i++)
        {
            img.setPixel(i, midY - vecData[i], qRgb(0, 255, 255)) ;
        }
    }

    if (isCheckedP78)
    {
        QVector<int> vecData ;
        QVector<int> c1(th->getP7()) ;
        QVector<int> c2(th->getP8()) ;
        vecDataP7 << c1 ;
        vecDataP7.erase(vecDataP7.begin(), vecDataP7.begin() + c1.size()) ;
        vecDataP8 << c2 ;
        vecDataP8.erase(vecDataP8.begin(), vecDataP8.begin() + c2.size()) ;

        for (int k = 0 ; k < vecDataP7.size() ; k++)
        {
            vecData.push_back((vecDataP7.at(k) + vecDataP8.at(k))/20 - 900) ;
            vecFoufou.replace(k, vecFoufou.at(k) + vecDataP7.at(k) + vecDataP8.at(k)) ;
        }
        for (int i = 0 ; i < vecData.size() ; i++)
        {
            img.setPixel(i, midY - vecData[i], qRgb(0, 0, 255)) ;
        }
    }

    if (isCheckedO12)
    {
        QVector<int> vecData ;
        QVector<int> c1(th->getO1()) ;
        QVector<int> c2(th->getO2()) ;
        vecDataO1 << c1 ;
        vecDataO1.erase(vecDataO1.begin(), vecDataO1.begin() + c1.size()) ;
        vecDataO2 << c2 ;
        vecDataO2.erase(vecDataO2.begin(), vecDataO2.begin() + c2.size()) ;

        for (int k = 0 ; k < vecDataO1.size() ; k++)
        {
            vecData.push_back((vecDataO1.at(k) + vecDataO2.at(k))/20 - 900) ;
            vecFoufou.replace(k, vecFoufou.at(k) + vecDataO1.at(k) + vecDataO2.at(k)) ;
        }
        for (int i = 0 ; i < vecData.size() ; i++)
        {
            img.setPixel(i, midY - vecData[i], qRgb(255, 0, 255)) ;
        }
    }

    sceneSignal.addPixmap(QPixmap::fromImage(img)) ;

}

void MainWindow::computeFFT()
{
    fftw_complex * out ;
    double * in ;
    fftw_plan p ;
    int ndata = vecFoufou.size() ;

    in = (double*) malloc(sizeof(double) * ndata) ;
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * ndata) ;

    QVector<double> c(vecFoufou) ;
    in = c.data() ;

    p = fftw_plan_dft_r2c_1d(ndata, in, out, 0) ;

    fftw_execute(p) ;
    fftw_destroy_plan(p) ;

    delta = 0 ;
    theta = 0 ;
    alpha = 0 ;
    beta = 0 ;
    gamma = 0 ;

    double fs = 128.0 ;
    for (int i = 0 ; i < ndata ; i++)
    {
        float valabs = log(1+sqrt(out[i][0]*out[i][0] + out[i][1]*out[i][1])/ndata) ;
        if (isnan(valabs))
            valabs = 0 ;

        float freq = -fs/2+i*fs/ndata ;

        float absf = fabs(freq) ;

        if (absf >= GAMMA_INF && absf < GAMMA_SUP)
            gamma+=valabs ;
        else if (absf >= BETA_INF && absf < GAMMA_INF)
            beta+=valabs ;
        else if (absf >= ALPHA_INF && absf < BETA_INF)
            alpha+=valabs ;
        else if (absf >= THETA_INF && absf < ALPHA_INF)
            theta+=valabs ;
        else if (absf >= DELTA_INF && absf < THETA_INF)
            delta+=valabs ;
    }

    fftw_free(out) ;
}

void MainWindow::drawFreq()
{
    float total = delta + theta + alpha + beta + gamma ;

    ui->progressDelta->setValue(delta/total*100) ;
    ui->progressTheta->setValue(theta/total*100) ;
    ui->progressAlpha->setValue(alpha/total*100) ;
    ui->progressBeta->setValue(beta/total*100) ;
    ui->progressTheta->setValue(gamma/total*100) ;


}



