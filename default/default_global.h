#ifndef DEFAULT_GLOBAL_H
#define DEFAULT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DEFAULT_LIBRARY)
#  define DEFAULTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define DEFAULTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // DEFAULT_GLOBAL_H
