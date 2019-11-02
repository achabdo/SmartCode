#-------------------------------------------------
#
# Project created by QtCreator 2014-12-20T10:14:55
#
#-------------------------------------------------

TARGET = classparser
TEMPLATE = lib

DEFINES += CLASSPARSER_LIBRARY

SOURCES += \
    classparsermodel.cpp \
    classparseritem.cpp

HEADERS +=\
        classparser_global.h \
    classparsermodel.h \
    classparseritem.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE3205B87
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = classparser.dll
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
