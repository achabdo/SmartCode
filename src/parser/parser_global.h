#ifndef PARSER_GLOBAL_H
#define PARSER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PARSER_LIBRARY)
#  define PARSERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define PARSERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PARSER_GLOBAL_H
