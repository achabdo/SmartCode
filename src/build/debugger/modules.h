#ifndef MODULES_H
#define MODULES_H

#include "build_global.h"
#include "debuggerclient.h"

class  BUILDSHARED_EXPORT  Modules : public DebuggerClient
{
    Q_OBJECT
public:
    explicit Modules(QWidget *parent = 0);
    ~Modules();

    QStringList headers() const;
    QString cmd() const;

protected:

    QString outputFormat() const;
    int linesToBeRemoved() const;

};

#endif // MODULES_H
