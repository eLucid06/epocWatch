#include "epocthread.hpp"

epocThread::epocThread(epocDevice * dev)
{
    device = dev ;
}

epocThread::~epocThread()
{

}

void epocThread::run()
{
    while(1)
    {
        device->update() ;
        vecCounter.push_back(device->getCounter()) ;
        vecAF3.push_back(device->getAF3()) ;
        vecAF4.push_back(device->getAF4()) ;
        vecF3.push_back(device->getF3()) ;
        vecF4.push_back(device->getF4()) ;
        vecF7.push_back(device->getF7()) ;
        vecF8.push_back(device->getF8()) ;
        vecFC5.push_back(device->getFC5()) ;
        vecFC6.push_back(device->getFC6()) ;
        vecT7.push_back(device->getT7()) ;
        vecT8.push_back(device->getT8()) ;
        vecP7.push_back(device->getP7()) ;
        vecP8.push_back(device->getP8()) ;
        vecO1.push_back(device->getO1()) ;
        vecO2.push_back(device->getO2()) ;
    }
}

QVector<int> epocThread::getCounter()
{
    QVector<int> v(vecCounter) ;
    vecCounter.clear() ;
    return v ;
}

QVector<int> epocThread::getAF3()
{
    QVector<int> v(vecAF3) ;
    vecAF3.clear() ;
    return v ;

}

QVector<int> epocThread::getAF4()
{
    QVector<int> v(vecAF4) ;
    vecAF4.clear() ;
    return v ;
}

QVector<int> epocThread::getF3()
{
    QVector<int> v(vecF3) ;
    vecF3.clear() ;
    return v ;

}

QVector<int> epocThread::getF4()
{
    QVector<int> v(vecF4) ;
    vecF4.clear() ;
    return v ;
}

QVector<int> epocThread::getF7()
{
    QVector<int> v(vecF7) ;
    vecF7.clear() ;
    return v ;
}

QVector<int> epocThread::getF8()
{
    QVector<int> v(vecF8) ;
    vecF8.clear() ;
    return v ;
}

QVector<int> epocThread::getFC5()
{
    QVector<int> v(vecFC5) ;
    vecFC5.clear() ;
    return v ;
}

QVector<int> epocThread::getFC6()
{
    QVector<int> v(vecFC6) ;
    vecFC6.clear() ;
    return v ;
}

QVector<int> epocThread::getT7()
{
    QVector<int> v(vecT7) ;
    vecT7.clear() ;
    return v ;
}

QVector<int> epocThread::getT8()
{
    QVector<int> v(vecT8) ;
    vecT8.clear() ;
    return v ;

}

QVector<int> epocThread::getP7()
{
    QVector<int> v(vecP7) ;
    vecP7.clear() ;
    return v ;
}

QVector<int> epocThread::getP8()
{
    QVector<int> v(vecP8) ;
    vecP8.clear() ;
    return v ;
}

QVector<int> epocThread::getO1()
{
    QVector<int> v(vecO1) ;
    vecO1.clear() ;
    return v ;
}

QVector<int> epocThread::getO2()
{
    QVector<int> v(vecO2) ;
    vecO2.clear() ;
    return v ;
}
