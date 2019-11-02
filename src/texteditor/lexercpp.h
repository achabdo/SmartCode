#ifndef LEXERCPP_H
#define LEXERCPP_H

#include "texteditor_global.h"
#include <Qsci/qscilexercpp.h>

class LexerStyle;

namespace TextEditor
{
class TEXTEDITORSHARED_EXPORT LexerCPP : public QsciLexerCPP
{
    Q_OBJECT
public:

    LexerCPP(LexerStyle *lexStyle,QObject *parent = 0, bool caseInsensitiveKeywords = false);

    QColor defaultColor(int style) const;
    QColor defaultPaper(int style) const;

    QFont defaultFont(int style) const;

    const char *data(const QStringList &list);
    const char *keywords(int set) const;

    void updateClasses(const QStringList &_classes) ;
    void updateGlobalVariables(const QStringList &vars);

    LexerStyle * style();

public slots:

private slots:

private:
    const char *classes;
    const char *globalVars;

    LexerStyle *lexerStyle;
};
}

#endif // LEXERCPP_H
