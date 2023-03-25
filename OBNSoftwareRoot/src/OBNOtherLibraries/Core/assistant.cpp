#include "assistant.h"
#include <QDesktopServices>

Assistant::Assistant()
{
}

bool Assistant::showAssistant(const QString &moduleName)
{
    QString m_EnvPath = Core::rootPath();
    QString  urlFileName = m_EnvPath+QString("/doc/GOBS_%1_Help.htm").arg(moduleName);
#if 1
    QDesktopServices::openUrl(QUrl::fromLocalFile(urlFileName));
#else
    QMainWindow * n_mainWindow = new QMainWindow;
    n_mainWindow->resize(1920, 1080);
    QWebEngineView * webView = new QWebEngineView(n_mainWindow);
    webView->resize(1920, 1080);
    webView->page()->load(QUrl::fromLocalFile(urlFileName));
    webView->show();
    n_mainWindow->show();
#endif
    return true;
}
