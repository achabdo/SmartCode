#ifndef GIT_H
#define GIT_H

#include "versioncontrol_global.h"

#include "versioncontrol.h"

class VERSIONCONTROLSHARED_EXPORT Git : public VersionControl
{
    Q_OBJECT
public:
    explicit Git(QObject *parent = 0);

    QString name() const;


protected:

    QString blameCommand() const;
    QString diffCommand() const;
    QString logCommand() const;
    QString addCommand() const;
    QString addRepositoryCommand() const;
    QString cloneRepositoryCommand() const;

signals:
    
public slots:
    
};

#endif // GIT_H
