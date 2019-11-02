#ifndef QTAPP_H
#define QTAPP_H
#include "compability_global.h"

#include <QObject>
#include <QProcess>

class Project;

class COMPABILITYSHARED_EXPORT QtApp : public QObject
{
    Q_OBJECT
public:
    explicit QtApp(QObject *parent = 0);

    void import(const QString &pro);
    void QtProjectFromSMC(Project *project);

    QString setConfg(const QString &confg,const QString &opr, const QStringList &paths);
    void start(const QString &proFile);

    void setQmake(const QString &qtProject);
signals:
    
public slots:

private:
    QString optionFromLine(const QString &line);
    QStringList pathsFromConfig(const QString &pro);
};

#endif // QTAPP_H
