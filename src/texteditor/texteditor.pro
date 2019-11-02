#-------------------------------------------------
#
# Project created by QtCreator 2013-12-29T15:23:28
#
#-------------------------------------------------
QT += gui xml printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = txted



TEMPLATE = lib
include(../../config.pri)
DEFINES += TEXTEDITOR_LIBRARY

equals(BUILD, "STATIC"){
CONFIG+=staticlib
}


CONFIG(staticlib) {
      DEFINES -= TEXTEDITOR_LIBRARY
}

CONFIG += create_prl

SOURCES += \
    textedit.cpp \
    lexercpp.cpp \
    insertfunctionswidget.cpp \
    lexerstyle.cpp \
    texteditbase.cpp \
    autocompleter.cpp \
    tabwidget.cpp \
    texteditmanager.cpp \
    lexergit.cpp \
    texteditarea.cpp \
    wordgenerator.cpp \
    synhighoptions.cpp \
    bookmarks.cpp \
    refactor.cpp \
    classparser.cpp

HEADERS += \
    texteditor_global.h \
    texteditbase.h \
    textedit.h \
    lexercpp.h \
    insertfunctionswidget.h \
    lexerstyle.h \  
    autocompleter.h \
    tabwidget.h \
    texteditmanager.h \
    lexergit.h \
    texteditarea.h \
    wordgenerator.h \
    synhighoptions.h \
    bookmarks.h \
    refactor.h \
    classparser.h

HEADERS += ../libs/qscintilla/Qt4Qt5/Qsci/qsciscintilla.h \
    ../libs/qscintilla/Qt4Qt5/Qsci/qsciscintillabase.h \
    ../libs/qscintilla/Qt4Qt5/Qsci/qscilexercpp.h \
    ../libs/qscintilla/Qt4Qt5/Qsci/qscilexercustom.h \
    ../libs/qscintilla/Qt4Qt5/Qsci/qscilexer.h \
    ../libs/qscintilla/Qt4Qt5/Qsci/qsciabstractapis.h \

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE4C96FDB
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = texteditor.dll
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
    insertfunctionswidget.ui \
    synhighoptions.ui

INCLUDEPATH += $$INCP/core\
               $$INCP/libs/qscintilla/Qt4Qt5 \
               $$INCP/versioncontrol \
               $$INCP/libs

equals(BUILD, "DYNAMIC"){
LIBS += -L$$DESTDIR -lcore -lvercontr -lastyle -lqscintilla2
}
