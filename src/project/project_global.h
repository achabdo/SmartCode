#ifndef PROJECT_GLOBAL_H
#define PROJECT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PROJECT_LIBRARY)
#  define PROJECTSHARED_EXPORT Q_DECL_EXPORT
//#else
//#  define PROJECTSHARED_EXPORT Q_DECL_IMPORT
#else
#  define PROJECTSHARED_EXPORT
#endif

#endif // PROJECT_GLOBAL_H
