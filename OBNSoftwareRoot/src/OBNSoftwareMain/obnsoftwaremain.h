#ifndef OBNSOFTWAREMAIN_H
#define OBNSOFTWAREMAIN_H

#include <QObject>
#include <QApplication>
#include <QDesktopWidget>

#include "obnwelcometotheinterface.h"
#include "obnmainwindow.h"

class OBNSoftwareMain : public QObject
{
    Q_OBJECT
public:
    OBNSoftwareMain();
    void initOBNSoftwareFunction();
private:
    OBNWelcomeToTheInterface* m_obnWelcome;
    OBNMainWindow*            m_obnMainWindow;
};

#endif // OBNSOFTWAREMAIN_H
