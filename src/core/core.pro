#-------------------------------------------------
#
# Project created by QtCreator 2013-12-29T16:04:44
#
#-------------------------------------------------

QT += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = lib

include(../../config.pri)

DEFINES += CORE_LIBRARY

equals(BUILD, "STATIC"){
CONFIG+=staticlib
}

CONFIG(staticlib) {
      DEFINES -= CORE_LIBRARY
}

CONFIG += create_prl

SOURCES += \
    dialog.cpp \
    recents.cpp \
    startpage.cpp \
    tabsetting.cpp \
    bases.cpp \
    settingsmanager.cpp \
    settingsdocument.cpp \
    tabsettingmanager.cpp \
    host.cpp \
    environment.cpp \
    buildvariables.cpp \
    variables.cpp \

HEADERS +=\
        core_global.h \
    core_constants.h \
    dialog.h \
    recents.h \
    startpage.h \
    tabsetting.h \
    bases.h \
    settingsmanager.h \
    settingsdocument.h \
    tabsettingmanager.h \
    host.h \
    environment.h \
    buildvariables.h \
    variables.h \

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE128486C
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = core.dll
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

RESOURCES += \
    resource.qrc

FORMS += \
    startpage.ui \
    tabsetting.ui \
    startProjects.ui
