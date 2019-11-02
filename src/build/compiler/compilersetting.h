#ifndef COMPILERSETTING_H
#define COMPILERSETTING_H

#include "build_global.h"

#include <settingsdocument.h>
#include <QtXml>
#include <QHash>
class Message;
class Compiler;

class BUILDSHARED_EXPORT CompilerSetting : public SettingsDocument
{

public:
  explicit CompilerSetting(const QString &name);

  bool isInEnvironmentPath();

  Compiler *compiler() const;
  bool load();

  QList<Message*> messages() const;
//  void readSettingManager(QDomElement &item);
protected:

private:

  Compiler * _compiler;
  QList<Message*> _messages;
};

#endif // COMPILERSETTING_H
