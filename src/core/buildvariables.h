#ifndef BUILDVARIABLES_H
#define BUILDVARIABLES_H

#include "core_global.h"
#include "variables.h"

class CORESHARED_EXPORT BuildVariables : public Variables
{
public:
    BuildVariables();

 bool evaluateCondition(const QString &exp);
 bool resolveCondition(const QString &exp, const QString &var, const QString &value);

 QStringList projectVariables() const;
private:


};

#endif // BUILDVARIABLES_H
