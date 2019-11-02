#ifndef ANALYZER_H
#define ANALYZER_H

#include <QObject>
#include <QHash>

class TextEditBase;


class Analyzer : public QObject
{
    Q_OBJECT
public:
    enum Type
    {
        identifier ,
        operators,
        string,
        value

    };


    explicit Analyzer(TextEditBase *edit,QObject *parent = 0);
    
    QList<int>  errors(const QString &code);

    bool identifierUsed(const QString &identifier, int pos);

    bool checkBrace(int pos);

signals:
    
public slots:

private:
    TextEditBase * editor;
};

#endif // ANALYZER_H
