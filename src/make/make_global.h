#ifndef MAKE_GLOBAL_H
#define MAKE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MAKE_LIBRARY)
#  define MAKESHARED_EXPORT Q_DECL_EXPORT
//#else
//#  define MAKESHARED_EXPORT Q_DECL_IMPORT
#else
#  define MAKESHARED_EXPORT
#endif

#endif // MAKE_GLOBAL_H
