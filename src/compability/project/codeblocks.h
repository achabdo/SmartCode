#ifndef CODEBLOCKS_H
#define CODEBLOCKS_H

#include "compability_global.h"
#include <QObject>

class COMPABILITYSHARED_EXPORT  CodeBlocks : public QObject
{
    Q_OBJECT
public:
    explicit CodeBlocks(QObject *parent = 0);

    void import(const QString &cbp);
    
signals:
    
public slots:
    
};
#endif // CODEBLOCKS_H
