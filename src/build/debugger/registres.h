#ifndef REGISTRES_H
#define REGISTRES_H

#include "build_global.h"
#include "debuggerclient.h"

class BUILDSHARED_EXPORT Registres : public DebuggerClient
{
public:
    Registres(QWidget * parent =0);
    ~Registres();

    void updateClient(const QString &output);

    QStringList headers() const;
    QString cmd() const;
protected:

    QString outputFormat() const;

};

#endif // REGISTRES_H
