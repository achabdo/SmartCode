#ifndef WATCHES_H
#define WATCHES_H

#include "debuggerclient.h"
#include <QDebug>
#include "build_global.h"

class BUILDSHARED_EXPORT Watches : public DebuggerClient
{
    Q_OBJECT
public:
    explicit Watches(QWidget *parent = 0);

    QStringList headers() const;
    void updateClient(const QString &output);
    QString cmd() const;
signals:
    
public slots:

    void addVariable(const QString &code);
private:
    int findMatchingBrace(const char ch, int pos, const QString &code);

protected:
    QString outputFormat() const;
};

#endif // WATCHES_H
