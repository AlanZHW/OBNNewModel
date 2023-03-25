#ifndef RNMANAGER_GLOBAL_H
#define RNMANAGER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(RNMANAGER_LIBRARY)
#define RNMANAGER_EXPORT Q_DECL_EXPORT
#else
#define RNMANAGER_EXPORT Q_DECL_IMPORT
#endif

#endif // RNMANAGER_GLOBAL_H
