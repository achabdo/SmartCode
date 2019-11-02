#ifndef DEVCPP_H
#define DEVCPP_H

#include "compability_global.h"

#include <QObject>
#include <QHash>
#include <QString>

class Project;
class COMPABILITYSHARED_EXPORT  DevCpp : public QObject
{
    Q_OBJECT
public:
    explicit DevCpp(QObject *parent = 0);
    void import(const QString &fileName);

signals:

public slots:
private:
    QHash<QString,QString> item;
};
#endif // DEVCPP_H
