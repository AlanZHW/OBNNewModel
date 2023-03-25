#include "obndeleteprojectinterface.h"
#include "ui_obndeleteprojectinterface.h"

OBNDeleteProjectInterface::OBNDeleteProjectInterface(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OBNDeleteProjectInterface)
{
    ui->setupUi(this);


    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    setupCurrentProjectList();

    connect(ui->pushButtonCancel, &QPushButton::clicked, this, &OBNDeleteProjectInterface::close);
    connect(ui->pushButtonDelete, &QPushButton::clicked, this, &OBNDeleteProjectInterface::slotDeleteProjectFunction);
}

OBNDeleteProjectInterface::~OBNDeleteProjectInterface()
{
    delete ui;
}

void OBNDeleteProjectInterface::setupCurrentProjectList()
{
    /// ====== 读取工区列表文件
    QStringList nProjectNameList, nProjectInformList;

    QString cfgFileName = QApplication::applicationDirPath() + Dir_Separator + "../.config/gobs_project.lt";
    QFileInfo fileInform(cfgFileName);
    if(fileInform.exists())
    {
        QFile fileRead(cfgFileName);
        if(fileRead.open(QIODevice::ReadOnly))
        {
            QString readData = fileRead.readAll();

            QJsonParseError parseJsonErr;
            QJsonDocument document = QJsonDocument::fromJson(readData.toUtf8(), &parseJsonErr);
            if(parseJsonErr.error == QJsonParseError::NoError)
            {
                QJsonObject jsonObject = document.object();
                for(QJsonObject::iterator iJson = jsonObject.begin(); iJson != jsonObject.end(); iJson ++)
                {
                    QString nJsonKey   = iJson.key();
                    nProjectNameList.append(nJsonKey);

                    QString nJsonValue = iJson.value().toString();
                    nProjectInformList.append(nJsonValue);
                }
            }
            fileRead.close();
        }
    }

    /// ====== 设置表格内容
    ui->tableWidget->setRowCount(nProjectInformList.count());
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setColumnWidth(0, this->width()/5);
    ui->tableWidget->setColumnWidth(1, this->width()/4);
    ui->tableWidget->setColumnWidth(2, this->width()/3);
    for(int iList = 0; iList < nProjectNameList.count(); iList ++)
    {
        QCheckBox* nCheckBox = new QCheckBox;
        ui->tableWidget->setCellWidget(iList, 0, nCheckBox);
        ui->tableWidget->setItem(iList, 1, new QTableWidgetItem(nProjectNameList.at(iList)));
        ui->tableWidget->setItem(iList, 2, new QTableWidgetItem(nProjectInformList.at(iList)));
    }

    /// ====== 释放存储信息链表
    nProjectNameList.clear();
    nProjectInformList.clear();
}

/// ====== 点击删除按钮,删除工区
void OBNDeleteProjectInterface::slotDeleteProjectFunction()
{
    /// ====== 判断工区信息表格是否为空,如果表格信息为空则弹出提示
    if(0 == ui->tableWidget->rowCount())
    {
        QMessageBox::information(this, tr("错误"), tr("工区列表为空,需要创建工区才能进行删除操作哦！"), tr("确定"));
        return;
    }
    /// ====== 获取需要删除的工区信息列表
    QStringList nCurrentDeleteProjectList;
    for(int iRow = 0; iRow < ui->tableWidget->rowCount(); iRow ++)
    {
        QCheckBox* nCheckBox = (QCheckBox*)ui->tableWidget->cellWidget(iRow, 0);
        if(nCheckBox->isChecked())
        {
            QString nRowPorjPathInform = ui->tableWidget->item(iRow, 2)->text();
            nCurrentDeleteProjectList.append(nRowPorjPathInform);

            /// ====== 删除表格内容
            ui->tableWidget->removeRow(iRow);
        }
    }
    if(0 == nCurrentDeleteProjectList.count())
    {
        QMessageBox::information(this, tr("错误"), tr("请选择需要删除的工区!"), tr("确定"));
        return;
    }
    /// ====== 删除磁盘工区路径
    QString rmCMD;
    for(int iList = 0; iList < nCurrentDeleteProjectList.count(); iList ++)
    {
        QDir nProjectPath(nCurrentDeleteProjectList.at(iList));
        if(nProjectPath.exists())
        {
            rmCMD = "rm -rf " + nCurrentDeleteProjectList.at(iList);
            system(rmCMD.toStdString().c_str());
        }
    }
    /// ====== 删除工区列表信息文件
    QStringList nProjectNameList, nProjectInformList;

    QString cfgFileName = QApplication::applicationDirPath() + Dir_Separator + "../.config/gobs_project.lt";
    QFile   fileRead(cfgFileName);
    if(fileRead.open(QIODevice::ReadOnly))
    {
        QString readData = fileRead.readAll();

        QJsonParseError parseJsonErr;
        QJsonDocument document = QJsonDocument::fromJson(readData.toUtf8(), &parseJsonErr);
        if(parseJsonErr.error == QJsonParseError::NoError)
        {
            QJsonObject jsonObject = document.object();
            for(QJsonObject::iterator iJson = jsonObject.begin(); iJson != jsonObject.end(); iJson ++)
            {
                QString nJsonKey   = iJson.key();
                QString nJsonValue = iJson.value().toString();
                if(-1 != nCurrentDeleteProjectList.indexOf(nJsonValue))
                {
                    continue;
                }
                nProjectInformList.append(nJsonValue);
                nProjectNameList.append(nJsonKey);
            }
        }
        fileRead.close();
    }
    /// ====== 删除旧的文件
    fileRead.remove();
    /// ====== 创建新的工区信息列表文件
    if(0 != nProjectNameList.count())
    {
        /// ====== 创建新的工区列表信息文件
        QFile fileWrite(cfgFileName);
        if(fileWrite.open(QIODevice::WriteOnly))
        {
            QJsonObject jsonObject;
            for(int iList = 0; iList < nProjectNameList.count(); iList ++)
            {
                QString nKeyInform   = nProjectNameList[iList];
                QString nValueInform = nProjectInformList[iList];
                jsonObject.insert(nKeyInform, nValueInform);
            }
            QJsonDocument documentToString;
            documentToString.setObject(jsonObject);
            QByteArray byteArray = documentToString.toJson(QJsonDocument::Compact);
            /// ======
            fileWrite.write(byteArray);
            /// ======
            fileWrite.close();
        }
    }
    /// ====== 弹出删除工区成功提示
    QMessageBox::information(this, tr("成功"), tr("删除工区信息成功!"), tr("确定"));
    /// ====== 触发删除工区信息成功信号
    emit signalDeleteProjectSuccess();
    /// ====== 关闭创建工区成功窗体
    this->close();
}
