#ifndef SEARCH_GLOBAL_H
#define SEARCH_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SEARCH_LIBRARY)
#  define SEARCHSHARED_EXPORT Q_DECL_EXPORT
//#else
//#  define SEARCHSHARED_EXPORT Q_DECL_IMPORT
#else
#  define SEARCHSHARED_EXPORT
#endif

#endif // SEARCH_GLOBAL_H
