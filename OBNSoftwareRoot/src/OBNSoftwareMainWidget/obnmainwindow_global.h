#ifndef OBNMAINWINDOW_GLOBAL_H
#define OBNMAINWINDOW_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(OBNMAINWINDOW_LIBRARY)
#define OBNMAINWINDOW_EXPORT Q_DECL_EXPORT
#else
#define OBNMAINWINDOW_EXPORT Q_DECL_IMPORT
#endif

#endif // OBNMAINWINDOW_GLOBAL_H