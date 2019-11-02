#ifndef COMPILEROPTIONSCATEGORY_H
#define COMPILEROPTIONSCATEGORY_H


#include <QObject>

#include <QString>
#include <QList>

class CompilerOption;

class CompilerOptionsCategory :public  QObject
{
public:
    explicit CompilerOptionsCategory(const QString &name,QObject * parent = 0);

    void addCompilerOption(CompilerOption *option);
    QList<CompilerOption *> toCompilerOptions();

    QString name() const;
private:
    QList<CompilerOption*> compilerOptions;
    QString _name;
};

#endif // COMPILEROPTIONSCATEGORY_H
