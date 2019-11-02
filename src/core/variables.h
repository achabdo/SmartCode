#ifndef VARIABLES_H
#define VARIABLES_H

#include <QMap>
#include <QStringList>
#include "core_global.h"
class CORESHARED_EXPORT Variables
{
public:
  Variables();

  void addVariable(const QString &varName,const QString &value);
  void unset(const QString &varName);

  QStringList variables();

  QString value(const QString &varName);

  Variables & operator +=(Variables * other){

    foreach(QString var,other->variables())
      {
        _values.insert(var,other->value(var));
      }

    return *this;
  }

  void clear();

  QString evaluateExpression(QString expr);
  QString evaluateVariable(const QString &var);

  void fromList(const QStringList &list);
  QStringList toList();

protected:
  QMap<QString,QString> _values;
};

#endif // VARIABLES_H
