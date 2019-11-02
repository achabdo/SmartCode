#ifndef CONFIG_H
#define CONFIG_H

#include "project_global.h"
#include <settingsmanager.h>

class PROJECTSHARED_EXPORT Config : public SettingsManager
{

public:
  enum Template {App,Lib,SharedLib};

  explicit Config(const QString &name);
  static Config *fromOther(const Config &other);
  ~Config();

  QString destDirTarget() const;
  QString ext() const;

  QString type() const;

};

#endif // CONFIG_H
