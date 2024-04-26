#-------------------------------------------------
#
# Project created by QtCreator 2021-02-05T20:17:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ssvep
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    _matrix.cpp \
    ssveptestthread.cpp \
    collectdatathread.cpp \
    channel_sel_dialog.cpp

HEADERS  += widget.h \
    _matrix.h \
    ssveptestthread.h \
    collectdatathread.h \
    channel_sel_dialog.h

FORMS    += widget.ui \
    channel_sel_dialog.ui
