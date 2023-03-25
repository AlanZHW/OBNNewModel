#ifndef OBNCREATEPROJECTINTERFACE_H
#define OBNCREATEPROJECTINTERFACE_H

#include <QDir>
#include <QDebug>
#include <QDialog>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>
#include <QFileDialog>
#include <QJsonDocument>

#include "macro.h"

namespace Ui {
class OBNCreateProjectInterface;
}

class OBNCreateProjectInterface : public QDialog
{
    Q_OBJECT

public:
    /// ====== 构造函数
    explicit OBNCreateProjectInterface(QWidget *parent = nullptr);
    /// ====== 析构函数
    ~OBNCreateProjectInterface();

    /// ====== 判断工区是否存在,并显示检查信息
    bool getCheckProjectInform(const QString&, const QString&);
    /// ====== 创建工区目录结构
    bool createProject(const QString& _projectPath, const QString& _projectName, QString&);
    /// ======
    bool addProjectInform(const QString& _projectPath, const QString& _projectName, QString&);

public slots:
    /// ====== 获取工区路径
    void slotGetProjectPathButtonClicked();
    /// ====== 点击OK按钮创建工区
    void slotCreateProjectPathButtonClicked();
    /// ====== 工区名发生改变信号触发槽函数
    void slotPorjectNameChange(const QString&);
signals:
    /// ====== 创建工区成功信号
    void signalCreateProjectSuccess();

private:
    Ui::OBNCreateProjectInterface *ui;
};

#endif // OBNCREATEPROJECTINTERFACE_H
