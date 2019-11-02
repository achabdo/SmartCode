#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "core_global.h"

#include <variables.h>

class CORESHARED_EXPORT Environment : public Variables
{
public:
  Environment();

  QString searchInPath(const QString &fileName);

  QChar pathListSeparator();

  static Environment systemEnvironment();

  void appendOrSet(const QString &key, const QString &value, const QString &sep);
  void prependOrSet(const QString &key, const QString &value, const QString &sep);

  void appendOrSetPath(const QString &value);
  void prependOrSetPath(const QString &value);
private:

};

#endif // ENVIRONMENT_H
