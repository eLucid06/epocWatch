#-------------------------------------------------
#
# Project created by QtCreator 2014-07-07T09:42:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = epocWatch
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    epocDevice.cpp \
    epocthread.cpp

LIBS += ../epocWatch/lib/libemokit.a \
            -lmcrypt \
            -lhidapi-hidraw \
            -lfftw3

HEADERS  += mainwindow.hpp \
    epocDevice.hpp \
    epocthread.hpp

FORMS    += mainwindow.ui
