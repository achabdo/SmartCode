#ifndef DISASSEMBLY_H
#define DISASSEMBLY_H

#include "build_global.h"
#include "debuggerclient.h"

class  BUILDSHARED_EXPORT Disassembly : public DebuggerClient
{
    Q_OBJECT
public:
    explicit Disassembly(QWidget *parent = 0);
    ~Disassembly();

    QString cmd() const;

signals:

public slots:
protected:
     int linesToBeRemoved() const;
     QString outputFormat() const;

};

#endif // DISASSEMBLY_H
