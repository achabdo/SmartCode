#ifndef CORE_GLOBAL_H
#define CORE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CORE_LIBRARY)
#  define CORESHARED_EXPORT Q_DECL_EXPORT
//#else
//#  define CORESHARED_EXPORT Q_DECL_IMPORT
#else
#  define CORESHARED_EXPORT
#endif

#endif // CORE_GLOBAL_H
