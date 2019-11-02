#ifndef LEXERGIT_H
#define LEXERGIT_H

#include "texteditor_global.h"

#include <Qsci/qscilexercustom.h>

namespace TextEditor
{
class TEXTEDITORSHARED_EXPORT LexerGit : public QsciLexerCustom
{
    Q_OBJECT
public:
    enum {normal,plus,minus,arobaz};

    explicit LexerGit(QObject *parent = 0);

    void styleText(int start, int end);

    const char * language() const;
    QString description(int style) const;

    QColor defaultColor(int style) const;
    
signals:
    
public slots:
    
};
}

#endif // LEXERGIT_H
