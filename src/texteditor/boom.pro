#-------------------------------------------------
#
# Project created by QtCreator 2014-08-02T14:54:41
#
#-------------------------------------------------

QT       += core gui

TARGET = boom
TEMPLATE = app
CONFIG += qscintilla2
SOURCES += main.cpp\
        mainwindow.cpp \
    textedit.cpp \
    classparser.cpp \
    autocompleter.cpp \
    insertfunctionswidget.cpp \
    lexercpp.cpp

HEADERS  += mainwindow.h \
    textedit.h \
    classparser.h \
    autocompleter.h \
    insertfunctionswidget.h \
    lexercpp.h

FORMS    += mainwindow.ui \
    insertfunctionswidget.ui

INCLUDEPATH += D:/SmartCode/src/core
LIBS += D:/SmartCode/libcore.a
