#ifndef COMPABILITY_GLOBAL_H
#define COMPABILITY_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(COMPABILITY_LIBRARY)
#  define COMPABILITYSHARED_EXPORT Q_DECL_EXPORT
//#else
//#  define COMPABILITYSHARED_EXPORT Q_DECL_IMPORT
#else
#  define COMPABILITYSHARED_EXPORT
#endif

#endif // COMPABILITY_GLOBAL_H
