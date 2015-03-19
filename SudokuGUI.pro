#-------------------------------------------------
#
# Project created by QtCreator 2015-03-12T17:45:38
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SudokuGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    board.cpp

HEADERS  += mainwindow.h \
    board.h

FORMS    += mainwindow.ui

win32:RC_FILE = MyApp.rc

