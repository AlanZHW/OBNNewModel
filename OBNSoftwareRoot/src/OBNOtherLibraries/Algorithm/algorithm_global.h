#ifndef ALGORITHM_GLOBAL_H
#define ALGORITHM_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ALGORITHM_LIBRARY)
#  define ALGORITHMSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ALGORITHMSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ALGORITHM_GLOBAL_H
