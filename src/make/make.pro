#-------------------------------------------------
#
# Project created by QtCreator 2015-04-20T14:40:03
#
#-------------------------------------------------

QT       -= gui
QT       += xml

include(../../config.pri)

TARGET = makx
TEMPLATE = lib

DEFINES += MAKE_LIBRARY

equals(BUILD, "STATIC"){
CONFIG+=staticlib
}


CONFIG(staticlib) {
      DEFINES -= MAKE_LIBRARY
}

CONFIG += create_prl

SOURCES += \
    makefilegenerator.cpp

HEADERS +=\
        make_global.h \
    makefilegenerator.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH+=  $$INCP/core\
               $$INCP/project\
               $$INCP/build

equals(BUILD, "DYNAMIC"){
LIBS+=  -L$$DESTDIR -lcore -lprox -lbldx
}
