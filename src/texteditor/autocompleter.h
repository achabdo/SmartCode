#ifndef AUTOCOMPLETER
#define AUTOCOMPLETER

#include <Qsci/qsciabstractapis.h>

class QsciLexerCPP;
class ClassParser;

class AutoCompleter : public QsciAbstractAPIs
{
    Q_OBJECT
public:
    AutoCompleter(QsciLexer *lexer);

    QStringList callTips(const QStringList &context,int commas, QsciScintilla::CallTipsStyle style,
                         QList<int> &shifts);

    void autoCompletionSelected(const QString &sel);
    void updateAutoCompletionList(const QStringList &context, QStringList &list);

    QString autoComplete(char ch, int pos);
    bool load(const QStringList &list);

    void setClassParser( ClassParser * classParser);
signals:

private slots:
    void completeDir();
    void completeFunction();
private:
    QStringList acList;
    ClassParser * clParser ;
};

#endif // AUTOCOMPLETER
