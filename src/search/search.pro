#-------------------------------------------------
#
# Project created by QtCreator 2014-10-07T21:18:19
#
#-------------------------------------------------

QT += gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../../config.pri)

TARGET = search
TEMPLATE = lib

DEFINES += SEARCH_LIBRARY

equals(BUILD, "STATIC"){
CONFIG+=staticlib
}

CONFIG += create_prl

CONFIG(staticlib) {
      DEFINES -= SEARCH_LIBRARY
}

SOURCES += \
    textfinder.cpp \
    advancedsearch.cpp

HEADERS +=\
        search_global.h \
    textfinder.h \
    advancedsearch.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE5C325D5
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = search.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

FORMS += \
    textfinder.ui \
    advancedsearch.ui

INCLUDEPATH +=  $$INCP/project \
                $$INCP/libs/qscintilla/Qt4Qt5 \
                $$INCP/texteditor \
                $$INCP/core

equals(BUILD, "DYNAMIC"){
LIBS+=  -L$$DESTDIR -lcore -lqscintilla2 -ltxted -lprox
}
