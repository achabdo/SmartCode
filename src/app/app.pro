#-------------------------------------------------
#
# Project created by QtCreator 2013-12-29T17:18:50
#
#-------------------------------------------------


QT += core gui xml printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmartCode
TEMPLATE = app

CONFIG += create_prl

include(../../config.pri)


SOURCES += main.cpp \
    mainwindow.cpp \
    options.cpp

HEADERS  += \
    mainwindow.h \
    options.h

RC_FILE = smart.rc

FORMS    += mainwindow.ui \
    About.ui \
    options.ui

RESOURCES += \
    resource.qrc

INCLUDEPATH+=   \
                $$INCP/core \
                $$INCP/libs/qscintilla/Qt4Qt5 \
                $$INCP/texteditor \
                $$INCP/project \
                $$INCP/build \
                $$INCP/search \
                $$INCP/compability \
                $$INCP/make


LIBS+=    -L$$DESTDIR -lcore -lbldx -lqscintilla2 -ltxted -lprox -lsearch -lcompb -lmakx

OTHER_FILES += \
    ../../config.pri

ICON = myapp.icns

CONFIG += link_prl

#core.path = $$DESTDIR/core
#core.files = ../../core/*
#config.path =$$DESTDIR/config
#config.files = ../../config/*
#local.path =$$DESTDIR/local
#local.files = ../../local/*
#resources.path =$$DESTDIR/resources
#resources.files = ../../resources/*
#style.path =  $$DESTDIR/style
#style.files = ../../style/*

#INSTALLS += core config local resources style



