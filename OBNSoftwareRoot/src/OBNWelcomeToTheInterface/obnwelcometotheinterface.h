#ifndef OBNWELCOMETOTHEINTERFACE_H
#define OBNWELCOMETOTHEINTERFACE_H

#include "appglobal.h"
#include "obncreateprojectinterface.h"
#include "obneditporjectinterface.h"
#include "obndeleteprojectinterface.h"
#include "obnwelcometotheinterface_global.h"

#include <QtGlobal>
#include <QDebug>
#include <QWidget>
#include <QTranslator>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class OBNWelcomeToTheInterface; }
QT_END_NAMESPACE

class OBNWELCOMETOTHEINTERFACE_EXPORT OBNWelcomeToTheInterface : public QWidget
{
    Q_OBJECT
public:
    OBNWelcomeToTheInterface(QWidget *parent = nullptr);
    ~OBNWelcomeToTheInterface();

public slots:
    /// ====== 读取工区信息文件,获取工区列表
    void setupCurrentProjectListFunc();
    /// ======
    void slotFunctionToggleLanguageSelection(const int & index);
signals:
    void signalEnterSystem(const int&, const QString&, const QString&);   ///< 进入系统信号
private:
    OBNCreateProjectInterface* m_createProject;
    OBNEditPorjectInterface*   m_editProject;
    OBNDeleteProjectInterface* m_deleteProject;
    QTranslator m_translator;
    Ui::OBNWelcomeToTheInterface *ui;
};
#endif // OBNWELCOMETOTHEINTERFACE_H
