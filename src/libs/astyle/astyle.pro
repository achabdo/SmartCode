#-------------------------------------------------
#
# Project created by QtCreator 2015-03-22T20:04:18
#
#-------------------------------------------------

QT       -= core gui

CONFIG(debug , debug|release) {
   DESTDIR=../../../debug

} else {
    DESTDIR=../../../release
}

TARGET = astyle
TEMPLATE = lib

DEFINES += ASTYLE_LIB

CONFIG+=staticlib

CONFIG(staticlib) {
      DEFINES -= ASTYLE_LIB
}

CONFIG += create_prl

SOURCES += \
    src/ASBeautifier.cpp \
    src/ASEnhancer.cpp \
    src/ASFormatter.cpp \
    src/ASLocalizer.cpp \
    src/ASResource.cpp \
    src/astyle_main.cpp

HEADERS += \
    src/ASLocalizer.h \
    src/astyle.h \
    src/astyle_main.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
