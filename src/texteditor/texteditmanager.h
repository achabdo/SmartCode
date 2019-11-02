#ifndef TEXTEDITMANAGER_H
#define TEXTEDITMANAGER_H

#include "texteditor_global.h"
#include <QObject>

#include "lexercpp.h"
#include "lexergit.h"

class ClassParser;
class QStandardItem;
namespace TextEditor {

class LexerCPP;
class LexerGit;

}

class TEXTEDITORSHARED_EXPORT TextEditManager : public QObject
{

    Q_OBJECT
public:
    explicit TextEditManager(QObject *parent = 0);
    
    static TextEditor::LexerCPP * lexerCPP();
    static TextEditor::LexerGit * lexerGit();
    static ClassParser * classParer();

    static void setTopLevelItem(QStandardItem *item);
signals:
    
public slots:

private:

    void setupLexers();
};

#endif // TEXTEDITMANAGER_H
