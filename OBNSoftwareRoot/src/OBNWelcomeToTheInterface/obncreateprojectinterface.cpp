#include "obncreateprojectinterface.h"
#include "ui_obncreateprojectinterface.h"

#include <QRegExpValidator>

OBNCreateProjectInterface::OBNCreateProjectInterface(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OBNCreateProjectInterface)
{
    ui->setupUi(this);
    /// ====== 设置工区路径编辑框只读属性
    ui->lineEditProjectPath->setReadOnly(true);

    /// ======
    connect(ui->pushButtonGetPath,  &QPushButton::clicked, this, &OBNCreateProjectInterface::slotGetProjectPathButtonClicked);
    connect(ui->pushButtonCancel,   &QPushButton::clicked, this, &OBNCreateProjectInterface::close);
    connect(ui->pushButtonOK,       &QPushButton::clicked, this, &OBNCreateProjectInterface::slotCreateProjectPathButtonClicked);
    /// ======
    connect(ui->lineEditProjectName, &QLineEdit::textChanged, this, &OBNCreateProjectInterface::slotPorjectNameChange);
}

OBNCreateProjectInterface::~OBNCreateProjectInterface()
{
    delete ui;
}

/// ======
bool OBNCreateProjectInterface::getCheckProjectInform(const QString& pDirProj, const QString& pNameProj)
{
    QString nProjectInform = pDirProj + Dir_Separator + pNameProj;
    QDir dir(nProjectInform);
    if(dir.exists())
    {
        ui->label->setStyleSheet("QLabel{background-color:yellow}");
        ui->label->setText(tr("工区已存在"));
        return false;
    }
    ui->label->setStyleSheet("QLabel{background-color:transparent}");
    ui->label->setText("");
    return true;
}

/// ====== 工区名发生改变信号触发槽函数
void OBNCreateProjectInterface::slotPorjectNameChange(const QString& pTextProjName)
{
    QString projectPath    = ui->lineEditProjectPath->text().trimmed();
    if(!projectPath.isEmpty() && !pTextProjName.isEmpty())
    {
        getCheckProjectInform(projectPath, pTextProjName);
    }
}

/// ====== 选择工区路径
void OBNCreateProjectInterface::slotGetProjectPathButtonClicked()
{
#ifdef Q_OS_LINUX
    QString nProjectPath = "/home";
#elif defined (Q_OS_WIN32)
    QString nProjectPath = "C:\\";
#endif

    /// ======
    QString path = QFileDialog::getExistingDirectory(this, tr("选择工区路径"), nProjectPath);
    if(!path.isEmpty())
    {
        QString nNameProject = ui->lineEditProjectName->text().trimmed();
        if(!nNameProject.isEmpty())
        {
            if(getCheckProjectInform(path, nNameProject))
            {
                ui->lineEditProjectPath->setText(path);
            }
        }
        else
        {
            ui->lineEditProjectPath->setText(path);
        }
    }
}

/// ====== 确定创建工区,创建工区目录结构
void OBNCreateProjectInterface::slotCreateProjectPathButtonClicked()
{
    /// ====== 判断工区路径和工区名是否为空
    if(ui->lineEditProjectName->text().isEmpty())
    {
        QMessageBox::information(this, tr("错误"), tr("软件遇到一个错误:您的工区名称为空,请输入合适的工区名!"), tr("确定"));
        return;
    }
    if(ui->lineEditProjectPath->text().isEmpty())
    {
        QMessageBox::information(this, tr("错误"), tr("软件遇到一个错误:您设置的工区路径为空,请选择合适的工区路径!"), tr("确定"));
        return;
    }

    /// ====== 创建工区路径
    QString nProjectPath = ui->lineEditProjectPath->text().trimmed();
    QString nProjectName = ui->lineEditProjectName->text().trimmed();
    QString nCreateProjectFailedInform;
    /// ======
    if(!createProject(nProjectPath, nProjectName, nCreateProjectFailedInform))
    {
        QMessageBox::information(this, tr("错误"), tr("软件遇到一个错误:")+nCreateProjectFailedInform, tr("确定"));
        return;
    }
    /// ====== 增加新工区信息到工区信息存储表中
    if(!addProjectInform(nProjectPath, nProjectName, nCreateProjectFailedInform))
    {
        QMessageBox::information(this, tr("错误"), tr("软件遇到一个错误:")+nCreateProjectFailedInform, tr("确定"));
        return;
    }

    /// ====== 弹出创建工区成功提示
    QMessageBox::information(this, tr("成功"), tr("恭喜您，创建工区成功！"), tr("确定"));
    /// ====== 触发创建工区成功信号
    emit signalCreateProjectSuccess();
    /// ====== 关闭新建工区界面
    this->close();
}

/// ====== 将新的工区信息添加到工区信息列表中
bool OBNCreateProjectInterface::addProjectInform(const QString& _projectPath, const QString& _projectName, QString& pCreateProjFailedInform)
{
    QString nConfigFileName = QApplication::applicationDirPath() + Dir_Separator + "../.config/gobs_project.lt";
    /// ====== 工区信息
    QString nCurrentProjInfo= _projectPath + Dir_Separator + _projectName;
    /// ====== 判断工区列表文件是否存在
    QFileInfo fileInform(nConfigFileName);
    if(fileInform.exists()) ///< 当配置文件存在时,在配置文件中添加内容
    {
        QFile file(nConfigFileName);
        if(file.open(QIODevice::WriteOnly|QIODevice::ReadOnly))
        {
            /// ====== 读取旧的文件内容
            QString nInformJsonFile = file.readAll();
            if(nInformJsonFile.isEmpty())
            {
                QJsonObject jsonObject;
                jsonObject.insert(_projectName, nCurrentProjInfo);

                QJsonDocument documentToString;
                documentToString.setObject(jsonObject);
                QByteArray byteArray = documentToString.toJson(QJsonDocument::Compact);
                file.write(byteArray);
            }
            else
            {
                QJsonParseError parseJsonErr;
                QJsonDocument document = QJsonDocument::fromJson(nInformJsonFile.toUtf8(), &parseJsonErr);
                if (!(parseJsonErr.error == QJsonParseError::NoError))
                {
                    pCreateProjFailedInform = tr("");
                    return false;
                }
                QJsonObject jsonObject = document.object();
                jsonObject.insert(_projectName, nCurrentProjInfo);

                // 构建 Json 文档
                QJsonDocument documentToString;
                documentToString.setObject(jsonObject);
                QByteArray byteArray = documentToString.toJson(QJsonDocument::Compact);

                /// ======
                file.seek(0);

                /// ======
                file.write(byteArray);
            }
            file.close();
        }
    }
    else    ///< 当配置文件不存在时,创建配置文件
    {
        QFile file(nConfigFileName);
        if(file.open(QIODevice::WriteOnly))
        {
            QJsonObject jsonObject;
            jsonObject.insert(_projectName, nCurrentProjInfo);

            QJsonDocument documentToString;
            documentToString.setObject(jsonObject);
            QByteArray byteArray = documentToString.toJson(QJsonDocument::Compact);
            /// ======
            file.write(byteArray);

            /// ======
            file.close();
        }
    }
    return true;
}

/// ====== 创建工区目录结构
bool OBNCreateProjectInterface::createProject(const QString& _projectPath, const QString& _projectName, QString& pCreateProjFailedInform)
{
    QString projFile = _projectPath + Dir_Separator + _projectName;
    QDir dir(projFile);
    if(dir.exists())
    {
        /// ====== 项目存在，则清除所有内容
        dir.removeRecursively();
    }

    /// ====== 创建工区主目录
    if(!dir.mkdir(projFile))
    {
        pCreateProjFailedInform = tr("创建工区主目录失败,请检查路径是否有写权限!");
        return false;
    }

    /// ====== 创建Project 文件
    QString project = projFile + Dir_Separator + _projectName + Project_File_Suffix;
    QFile file(project);
    if(!file.open(QIODevice::WriteOnly))
    {
        pCreateProjFailedInform = tr("创建工区信息文件失败,请检查!");
        return false;
    }

    /// ====== 创建默认的数据保存目录，并保存当前数据值
    QString dataPath = projFile + Dir_Separator +"data";
    dir.setPath(dataPath);
    if(!dir.exists())
    {
        if(!dir.mkdir(dataPath))
        {
            pCreateProjFailedInform = tr("创建工区默认的数据保存目录失败,请检查!");
            return false;
        }
    }
    /// ====== 创建workPath /抽取道集作业记录工作目录
    QString workPath = projFile + Dir_Separator +"work";
    dir.setPath(workPath);
    if(!dir.exists())
    {
        if(!dir.mkdir(workPath))
        {
            pCreateProjFailedInform = tr("创建工区作业记录工作目录失败,请检查!");
            return false;
        }
    }

    /// ====== 创建GOBS文件下载记录文件
    QString downloadFile = projFile + Dir_Separator + _projectName + Project_Download_Suffix;
    QFile file1(downloadFile);
    file1.open(QIODevice::WriteOnly);
    file1.close();

    QJsonObject jobj;
    jobj.insert(Json_Key_Project_Indentity,QJsonValue(Json_Value_Project_Indentity));
    jobj.insert(Json_Key_Project_Areas,    QJsonArray());
    jobj.insert(Json_Key_Project_Data_Path,QJsonValue(dataPath));
    jobj.insert(Json_Key_Project_Work_Path,QJsonValue(workPath));
    jobj.insert(Json_Key_Project_Download, QJsonValue(downloadFile));

    QJsonDocument doc;
    doc.setObject(jobj);

    file.write(doc.toJson());
    file.close();

    return true;
}






