#include "obnsoftwaremain.h"

OBNSoftwareMain::OBNSoftwareMain() :
    m_obnWelcome(NULL)
    ,m_obnMainWindow(NULL)
{
    initOBNSoftwareFunction();
}

void OBNSoftwareMain::initOBNSoftwareFunction()
{
#if 0
    if(NULL == m_obnWelcome)
    {
        m_obnWelcome = new OBNWelcomeToTheInterface;
        connect(m_obnWelcome, &OBNWelcomeToTheInterface::signalEnterSystem, this, [=](const int& lMode, const QString& _projectName, const QString& _projectText){

            qDebug() << "lMode = " << lMode;
            qDebug() << "_projectName = " << _projectName;
            qDebug() << "_projectText = " << _projectText;

            /// ====== 关闭欢迎界面
            if(NULL != m_obnWelcome)
            {
                m_obnWelcome->close();
            }
            /// ====== 打开软件主界面
            if(NULL != m_obnMainWindow)
            {
                m_obnMainWindow->close();
                delete m_obnMainWindow;
                m_obnMainWindow = NULL;
            }
            /// ======
            m_obnMainWindow = new OBNMainWindow;
            m_obnMainWindow->setCurrentProjectInfrom(_projectName, _projectText);
            m_obnMainWindow->show();
        });
    }
    /// ====== 设置欢迎界面居中显示
    QDesktopWidget *desktop = QApplication::desktop();
    m_obnWelcome->move((desktop->width()-m_obnWelcome->width())/2, (desktop->height()-m_obnWelcome->height())/2);
    m_obnWelcome->show();
#else
    QString _projectName = "ProjectName";
    QString _projectText = "/home/datuo/ZHW/TestPath/ProjectName";

    /// ====== 打开软件主界面
    if(NULL != m_obnMainWindow)
    {
        m_obnMainWindow->close();
        delete m_obnMainWindow;
        m_obnMainWindow = NULL;
    }
    /// ======
    m_obnMainWindow = new OBNMainWindow;
    m_obnMainWindow->setCurrentProjectInfrom(_projectName, _projectText);
    m_obnMainWindow->show();
#endif
}


