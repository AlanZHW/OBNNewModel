#ifndef OBNLMGRAREALISTWIDGET_H
#define OBNLMGRAREALISTWIDGET_H

#include <QDebug>
#include <QDialog>
#include <QMessageBox>

#include "projectarea.h"
#include "publicHostInform.h"
#include "obnlmgrarealistwidget_global.h"

QT_BEGIN_NAMESPACE
namespace Ui { class OBNLMGRAreaListWidget; }
QT_END_NAMESPACE

class OBNLMGRAREALISTWIDGET_EXPORT OBNLMGRAreaListWidget : public QDialog
{
    Q_OBJECT

public:
    OBNLMGRAreaListWidget(QWidget *parent = nullptr);
    ~OBNLMGRAreaListWidget();
    /// ====== 设置工区信息
    void setProjectInform(const QString& _projectPath, const QString& _projectName);
    /// ====== 初始化当前表格
    void initTableWidget();

signals:
    void signalCurrentAreaName(const QString&);

public slots:
    void slotSelectArea(const bool&);

private:
    ProjectInfo m_projInform;

    Ui::OBNLMGRAreaListWidget *ui;
};
#endif // OBNLMGRAREALISTWIDGET_H
