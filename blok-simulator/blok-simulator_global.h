#ifndef BLOKSIMULATOR_GLOBAL_H
#define BLOKSIMULATOR_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(BLOKSIMULATOR_LIBRARY)
#  define BLOKSIMULATORSHARED_EXPORT Q_DECL_EXPORT
#else
#  define BLOKSIMULATORSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // BLOKSIMULATOR_GLOBAL_H
