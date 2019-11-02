#ifndef STACK_H
#define STACK_H

#include "build_global.h"
#include "debuggerclient.h"

class BUILDSHARED_EXPORT Stack : public DebuggerClient
{
    Q_OBJECT
public:
    explicit Stack(QWidget *parent = 0);
    ~Stack();

  QString cmd() const;
  QStringList headers() const;


signals:

public slots:
protected:
  QString outputFormat() const;
};

#endif // STACK_H
