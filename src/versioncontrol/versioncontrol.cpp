#include "versioncontrol.h"

#include <QDebug>

VersionControl::VersionControl(QObject *parent) :
    QObject(parent)
{

}

void VersionControl::addFile(const QString &fileName)
{   
    executePathCmd(addCommand(),fileName);
}

QString VersionControl::blame(const QString &fileName)
{
    return readFromProcess(blameCommand(),fileName);
}

QString VersionControl::diff(const QString &fileName)
{
    return readFromProcess(diffCommand(),fileName);
}

QString VersionControl::log(const QString &fileName)
{
    return readFromProcess(logCommand(),fileName);
}

QString VersionControl::readFromProcess(const QString &cmd,const QString &fileName)
{
    executePathCmd(cmd,fileName);

    if(process.waitForFinished())
        return process.readAllStandardOutput();

    return QString();
}

QString VersionControl::name() const
{
    return QString();
}

QString VersionControl::blameCommand() const
{
    return QString();
}

QString VersionControl::diffCommand() const
{
    return QString();
}

QString VersionControl::logCommand() const
{
    return QString();
}

QString VersionControl::addCommand() const
{
    return QString();
}

QString VersionControl::addRepositoryCommand() const
{
    return QString();
}

QString VersionControl::cloneRepositoryCommand() const
{
    return QString();
}

void VersionControl::addRepository()
{
    executeCmd(addRepositoryCommand());
}

void VersionControl::cloneRepository()
{
    executeCmd(cloneRepositoryCommand());
}

void VersionControl::execute(const QStringList &args)
{
    process.start(name(),args);
}

void VersionControl::executeCmd(const QString &cmd)
{
    execute(QStringList()<<cmd);
}

void VersionControl::executePathCmd(QString cmd ,const QString &path)
{
    execute(QStringList()<<cmd<<path);
}


