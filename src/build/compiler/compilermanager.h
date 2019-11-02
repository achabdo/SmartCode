#ifndef COMPILERMANAGER_H
#define COMPILERMANAGER_H

#include <QList>
#include <QStringList>

class Compiler;

class CompilerManager
{
public:
    CompilerManager();

    void addCompiler(Compiler * compiler);
    void removeCompiler(Compiler * compiler);
    void cloneCompiler(Compiler * base);

    Compiler * compiler(const QString &compilerName);

    QStringList avaibleCompilers();
private:
    QList<Compiler*> _compilers;
};

#endif // COMPILERMANAGER_H
