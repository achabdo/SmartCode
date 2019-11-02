#ifndef THREADS_H
#define THREADS_H

#include "build_global.h"

#include "debuggerclient.h"

class BUILDSHARED_EXPORT Threads : public DebuggerClient
{
    Q_OBJECT
public:
    Threads(QWidget *parent = 0);
    ~Threads();

    QString cmd() const;
    QStringList headers() const;

signals:

public slots:

protected:

    QString outputFormat() const;
};

#endif // THREADS_H
