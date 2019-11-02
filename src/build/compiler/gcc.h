#ifndef GCC_H
#define GCC_H

#include "compiler.h"
#include <QRegularExpression>
#include "message.h"

class Gcc : public Compiler
{
public:
  Gcc(const QString &path);
  virtual QString name() const;
//  virtual QString make() const;

  void autoDetecte(const QString &compiler);

  virtual QList<CompilerOptionsCategory*> flags();

  void parse(const QString &line);


  virtual QString CC() const;

  virtual QString CXX() const;

  virtual QString dynamicLibLinker() const;

  virtual QString staticLibLinker() const;

  virtual QString make() const;

  virtual QString makeCommand() const;

  virtual QString resourceCompiler() const;

  virtual QString debugger() const;
private:
  QRegularExpression  regExp,regExpIncluded,regExpGccNames;
  void newMessage(const Message::MessageType &_type, const QString &description
                  , const QString &fileName = QString(), int lineno = -1);
  void doFlush();
  void expandDescription(const QString &desc);
  Message _currentMessage;
};

class Mingw : public Gcc
{
public:
  Mingw(const QString &path);
  QString name() const;
  QString make() const;
private:

};

#endif // GCC_H
