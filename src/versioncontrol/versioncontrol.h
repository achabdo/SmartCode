#ifndef VERSIONCONTROL_H
#define VERSIONCONTROL_H

#include "versioncontrol_global.h"

#include <QObject>
#include <QProcess>

class VERSIONCONTROLSHARED_EXPORT VersionControl : public QObject
{
    Q_OBJECT
public:
    explicit VersionControl(QObject *parent = 0);

    void lunch();

    void addFile(const QString &fileName);

    void addRepository();
    void cloneRepository();

    void execute(const QStringList &args);
    void executePathCmd(QString cmd , const QString &path);

    QString blame(const QString &fileName);
    QString diff(const QString & fileName);
    QString log(const QString &fileName);

    virtual QString name() const;


signals:

public slots:

protected:

    virtual QString blameCommand() const;
    virtual QString diffCommand() const;
    virtual QString logCommand() const;
    virtual QString addCommand() const;
    virtual QString addRepositoryCommand() const;
    virtual QString cloneRepositoryCommand() const;

private:
  QString readFromProcess(const QString &cmd, const QString &fileName);
  void executeCmd(const QString & cmd);

  QProcess process;

    
};

#endif // VERSIONCONTROL_H
