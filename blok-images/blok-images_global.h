#ifndef BLOKIMAGES_GLOBAL_H
#define BLOKIMAGES_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(BLOKIMAGES_LIBRARY)
#  define BLOKIMAGESSHARED_EXPORT Q_DECL_EXPORT
#else
#  define BLOKIMAGESSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // BLOKIMAGES_GLOBAL_H
