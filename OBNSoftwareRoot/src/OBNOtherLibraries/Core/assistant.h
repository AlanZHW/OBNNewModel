#ifndef ASSISTANT_H
#define ASSISTANT_H

#include <QProcess>
#include "core.h"
#include "core_global.h"

#include <QMainWindow>
//#include <QWebEngineView>

class CORESHARED_EXPORT Assistant
{
public:
    Assistant();
    static bool showAssistant(const QString &moduleName);
};

#endif // ASSISTANT_H
