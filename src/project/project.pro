#-------------------------------------------------
#
# Project created by QtCreator 2013-12-29T15:55:50
#
#-------------------------------------------------

QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = prox
TEMPLATE = lib
include(../../config.pri)
DEFINES += PROJECT_LIBRARY

equals(BUILD, "STATIC"){
CONFIG+=staticlib
}

CONFIG(staticlib) {
      DEFINES -= PROJECT_LIBRARY
}

CONFIG += create_prl

SOURCES += \
    projecttemplate.cpp \
    projectdir.cpp \
    projectdialog.cpp \
    project.cpp \
    configwizard.cpp \
    classgenerator.cpp \
    projectexplorer.cpp \
    newfilewizard.cpp \
    projectwizard.cpp \
    projectsummarywizard.cpp \
    classparsermanager.cpp \
    projectsetting.cpp \
    config.cpp \
    configmanager.cpp \
    runconfig.cpp

HEADERS +=\
        project_global.h \
    projecttemplate.h \
    projectdir.h \
    projectdialog.h \
    project.h \
    configwizard.h \
    classgenerator.h \
    projectexplorer.h \
    newfilewizard.h \
    projectwizard.h \
    projectsummarywizard.h \
    classparsermanager.h \
    projectsetting.h \
    config.h \
    configmanager.h \
    runconfig.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE40E22B7
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = project.dll
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
    projectdir.ui \
    projectdialog.ui \
    configwizard.ui \
    classgenerator.ui \
    newfilewizard.ui \
    projectsummarywizard.ui \
    dependencies.ui \
    projectsetting.ui

INCLUDEPATH+=  $$INCP/core\
               $$INCP/libs/qscintilla/Qt4Qt5 \
               $$INCP/texteditor\
               $$INCP/build
equals(BUILD, "DYNAMIC"){
LIBS+=  -L$$DESTDIR -lcore -ltxted -lbldx
}
RESOURCES += \
    resources.qrc
