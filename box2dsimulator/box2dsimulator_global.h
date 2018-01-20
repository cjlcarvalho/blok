#ifndef BOX2DSIMULATOR_GLOBAL_H
#define BOX2DSIMULATOR_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(BOX2DSIMULATOR_LIBRARY)
#  define BOX2DSIMULATORSHARED_EXPORT Q_DECL_EXPORT
#else
#  define BOX2DSIMULATORSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // BOX2DSIMULATOR_GLOBAL_H