#-------------------------------------------------
#
# Project created by QtCreator 2015-07-10T18:57:54
#
#-------------------------------------------------

QT       += gui

TARGET = parser
TEMPLATE = lib

include(../../config.pri)

DEFINES += PARSER_LIBRARY

SOURCES +=

HEADERS +=\
        parser_global.h \
    document.h \
    classview.h \
    documentdiagnosticclient.h \
    preprocessor.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += ../libs \
                ../core
LIBS += $$DESTDIR/libcplusplus.a \
        $$DESTDIR/libcore.a
