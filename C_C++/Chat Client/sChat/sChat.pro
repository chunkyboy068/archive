#-------------------------------------------------
#
# Project created by QtCreator 2012-12-06T10:03:23
#
#-------------------------------------------------

QT       += core gui
QT	 += network

TARGET = sChat
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    clientModel.cpp \
    connector.cpp \
    failwindow.cpp \
    qonsole.cpp

HEADERS  += mainwindow.h \
    clientModel.h \
    connector.h \
    failwindow.h \
    qonsole.h

FORMS    += mainwindow.ui \
    connector.ui \
    failwindow.ui \
    qonsole.ui
