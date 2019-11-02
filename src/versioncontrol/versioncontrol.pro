#-------------------------------------------------
#
# Project created by QtCreator 2014-11-10T11:12:33
#
#-------------------------------------------------

QT       -= gui

TARGET = vercontr

include(../../config.pri)

TEMPLATE = lib

DEFINES += VERSIONCONTROL_LIBRARY

equals(BUILD, "STATIC"){
CONFIG+=staticlib
}


CONFIG += create_prl

CONFIG(staticlib) {
      DEFINES -= VERSIONCONTROL_LIBRARY
}

SOURCES += \
    versioncontrol.cpp \
    git.cpp

HEADERS +=\
        versioncontrol_global.h \
    versioncontrol.h \
    git.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE094DA35
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = versioncontrol.dll
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
