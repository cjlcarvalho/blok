#ifndef SNOW_GLOBAL_H
#define SNOW_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SNOW_LIBRARY)
#  define SNOWSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SNOWSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SNOW_GLOBAL_H
