#ifndef RUNCONFIG_H
#define RUNCONFIG_H

#include "project_global.h"
#include <settingsmanager.h>

class PROJECTSHARED_EXPORT RunConfig : public SettingsManager
{

public:
  explicit RunConfig(const QString &name);

  QString type() const;
};

#endif // RUNCONFIG_H
