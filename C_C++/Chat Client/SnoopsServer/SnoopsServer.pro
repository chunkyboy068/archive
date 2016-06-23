#-------------------------------------------------
#
# Project created by QtCreator 2012-12-07T00:35:09
#
#-------------------------------------------------

QT       += core gui
QT	 += network

TARGET = SnoopsServer
TEMPLATE = app


SOURCES += main.cpp\
        snoopsgui.cpp \
    SSLServer.cpp \
    serverbackend.cpp

HEADERS  += snoopsgui.h \
    SSLServer.h \
    serverbackend.h

FORMS    += snoopsgui.ui
