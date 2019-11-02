#include "compilermanager.h"
#include "compiler.h"

CompilerManager::CompilerManager()
{

}

QStringList CompilerManager::avaibleCompilers()
{

}

void CompilerManager::addCompiler(Compiler *compiler)
{
  _compilers << compiler;
}

void CompilerManager::removeCompiler(const Compiler *compiler)
{
  _compilers.removeOne(compiler);
}

void CompilerManager::cloneCompiler(Compiler *base)
{
  Compiler * clone = new Compiler;
  clone->fromMap(base->toMap());
}

Compiler *CompilerManager::compiler(const QString &compilerName)
{
  foreach(Compiler *c,_compilers)
    {
      if(c->name() == compilerName)
        return c;
    }

  return Compiler();
}

