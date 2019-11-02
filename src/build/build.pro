#-------------------------------------------------
#
# Project created by QtCreator 2013-12-29T17:05:16
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bldx
TEMPLATE = lib
include(../../config.pri)
DEFINES += BUILD_LIBRARY

equals(BUILD, "STATIC"){
CONFIG+=staticlib
}


CONFIG(staticlib) {
      DEFINES -= BUILD_LIBRARY
}

CONFIG += create_prl

SOURCES += \
    compiler/compilersetting.cpp \
    debugger/debugger.cpp \
    debugger/watches.cpp \
    logs/log.cpp \
    logs/problems.cpp \
    logs/logs.cpp \
    debugger/breakpoints.cpp \
    debugger/threads.cpp \
    debugger/registres.cpp \
    debugger/disassembly.cpp \
    debugger/stack.cpp \
    debugger/examinememory.cpp \
    debugger/modules.cpp \
    debugger/breakpoint.cpp \
    debugger/breakpointwidget.cpp \
    debugger/breakpointsmanager.cpp \
    debugger/debuggerclientwidget.cpp \
    debugger/debuggerclient.cpp \
    debugger/gdb.cpp \
    compiler/buildmanager.cpp \
    compiler/compilersettingwidget.cpp \
    compiler/compiler.cpp \
    compiler/compileroption.cpp \
    compiler/compileroptionscategory.cpp \
    compiler/compileroptionswidget.cpp \
    compiler/gcc.cpp \
    compiler/message.cpp \
   # compiler/compilermanager.cpp

HEADERS +=\
        build_global.h \
    compiler/compilersetting.h \
    debugger/watches.h \
    logs/log.h \
    logs/problems.h \
    logs/logs.h \
    debugger/breakpoints.h \
    debugger/debugger.h \
    debugger/threads.h \
    debugger/registres.h \
    debugger/disassembly.h \
    debugger/stack.h \
    debugger/examinememory.h \
    debugger/modules.h \
    debugger/breakpoint.h \
    debugger/breakpointwidget.h \
    debugger/breakpointsmanager.h \
    debugger/debuggerclientwidget.h \
    debugger/debuggerclient.h \
    debugger/gdb.h \
    compiler/buildmanager.h \
    compiler/compiler.h \
    compiler/compilersettingwidget.h \
    compiler/compileroption.h \
    compiler/compileroptionscategory.h \
    compiler/compileroptionswidget.h \
    compiler/gcc.h \
    compiler/message.h \
   # compiler/compilermanager.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE0AF958A
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = build.dll
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
INCLUDEPATH += . $$INCP/core

equals(BUILD, "DYNAMIC"){
LIBS +=  -L$$DESTDIR -lcore
}



RESOURCES += \
    res.qrc

FORMS += \
    debugger/examinememory.ui \
    compiler/compilersettingwidget.ui \
    debugger/breakpointwidget.ui
