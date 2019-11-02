#ifndef BREAKPOINTS_H
#define BREAKPOINTS_H

#include "build_global.h"

#include "debuggerclient.h"

class BreakPoints : public DebuggerClient
{
    Q_OBJECT
public:

    BreakPoints(QWidget * parent = 0);
    ~BreakPoints();

    QStringList headers() const;
    QString cmd() const;
protected:

    QString outputFormat() const;
};

#endif // BREAKPOINTS_H
