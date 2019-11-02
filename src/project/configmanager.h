#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include "project_global.h"

#include <QObject>

class CompilerSetting;
class Config;

class PROJECTSHARED_EXPORT ConfigManager : public QObject
{
    Q_OBJECT
public:
    explicit ConfigManager(CompilerSetting * compilerSetting,QObject *parent = 0);
    ~ConfigManager();

  Config *addDefaultConfig(const QString &configName);
  Config *addDebugConfig(const QString &name = "Debug");
  Config *addReleaseConfig(const QString &name = "Release");

signals:

public slots:
private:
  CompilerSetting * compilerSetting;
};

#endif // CONFIGMANAGER_H
