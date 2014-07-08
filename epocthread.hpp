#ifndef EPOCTHREAD_HPP
#define EPOCTHREAD_HPP

#include <QThread>
#include <QVector>
#include <QDebug>
#include <epocDevice.hpp>

class epocThread : public QThread
{
public:
    epocThread(epocDevice *) ;
    ~epocThread() ;

    void run() ;

    QVector<int> getCounter() ;
    QVector<int> getAF3() ;
    QVector<int> getAF4() ;
    QVector<int> getF3() ;
    QVector<int> getF4() ;
    QVector<int> getF7() ;
    QVector<int> getF8() ;
    QVector<int> getFC5() ;
    QVector<int> getFC6() ;
    QVector<int> getT7() ;
    QVector<int> getT8() ;
    QVector<int> getP7() ;
    QVector<int> getP8() ;
    QVector<int> getO1() ;
    QVector<int> getO2() ;

private:
    epocDevice * device ;
    int to_erase ;
    QVector<int> vecAF3, vecAF4, vecF3, vecF4, vecF7, vecF8, vecFC5, vecFC6, vecT7, vecT8, vecP7, vecP8, vecO1, vecO2, vecCounter ;
} ;

#endif // EPOCTHREAD_HPP
