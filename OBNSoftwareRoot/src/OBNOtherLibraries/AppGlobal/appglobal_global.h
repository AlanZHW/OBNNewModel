#ifndef APPGLOBAL_GLOBAL_H
#define APPGLOBAL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(APPGLOBAL_LIBRARY)
#define APPGLOBAL_EXPORT Q_DECL_EXPORT
#else
#define APPGLOBAL_EXPORT Q_DECL_IMPORT
#endif

#endif // APPGLOBAL_GLOBAL_H
