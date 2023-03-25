#ifndef OBNDELETEPROJECTINTERFACE_H
#define OBNDELETEPROJECTINTERFACE_H

#include <QDir>
#include <QFile>
#include <QDebug>
#include <QDialog>
#include <QFileInfo>
#include <QCheckBox>
#include <QJsonObject>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonParseError>

#include "macro.h"

namespace Ui {
class OBNDeleteProjectInterface;
}

class OBNDeleteProjectInterface : public QDialog
{
    Q_OBJECT

public:
    explicit OBNDeleteProjectInterface(QWidget *parent = nullptr);
    ~OBNDeleteProjectInterface();

    /// ====== 设置当前工区信息列表
    void setupCurrentProjectList();

public slots:
    /// ====== 点击删除工区信息按钮
    void slotDeleteProjectFunction();

signals:
    void signalDeleteProjectSuccess();

private:
    Ui::OBNDeleteProjectInterface *ui;
};

#endif // OBNDELETEPROJECTINTERFACE_H
