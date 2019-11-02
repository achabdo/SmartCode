#ifndef COMPILER_H
#define COMPILER_H

#include "build_global.h"
#include <QString>
#include "compileroptionscategory.h"
#include <QObject>
class Message;

class BUILDSHARED_EXPORT Compiler : public QObject
{
   Q_OBJECT
signals:
  void addMessage(const Message &msg);
public:
  Compiler(const QString &path);

  virtual QString name() const = 0;

  virtual QString CC() const;
  virtual QString CXX()const;
  virtual QString dynamicLibLinker() const;
  virtual QString staticLibLinker() const;
  virtual QString make() const;
  virtual QString makeCommand() const;
  virtual QString resourceCompiler()const;
  virtual QString debugger() const;

  void setPath(const QString &path);
  QString getPath() const;

  virtual QList<CompilerOptionsCategory*> flags() const;

  virtual void autoDetecte ();

  virtual void parse(const QString &);
private :
  QString path;
};

#endif // COMPILER_H
