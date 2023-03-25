#include "obnwelcometotheinterface.h"
#include "ui_obnwelcometotheinterface.h"

OBNWelcomeToTheInterface::OBNWelcomeToTheInterface(QWidget *parent)
    : QWidget(parent), m_createProject(NULL), m_editProject(NULL), m_deleteProject(NULL)
    , ui(new Ui::OBNWelcomeToTheInterface)
{
    ui->setupUi(this);

    /// ======
    setFixedSize(800, 643);
    setWindowTitle(tr("欢迎使用OBN软件"));
    //setWindowIcon(QIcon(":bootImage/img/tubiao.png"));
    //setWindowIconText(tr("OBN数据管理软件"));

//    /// ====== 显示欢迎界面图像
//    QPixmap pixmap(":bootImage/img/bootAnimation.png");
//    QPalette palette;
//    palette.setBrush(ui->frameWelcomeImage->backgroundRole(), QBrush(pixmap));
//    ui->frameWelcomeImage->setPalette(palette);
//    ui->frameWelcomeImage->setAutoFillBackground(true);

    /// ====== 设置显示文字部分
    ui->textBrowser->setReadOnly(true);
    ui->textBrowser->setOpenLinks(false);
    ui->textBrowser->setOpenExternalLinks(false);

    /// ====== 读取工区信息文件,获取工区列表
    setupCurrentProjectListFunc();

    /// ====== 点击文字显示区域中的超链接文字时,触发信号调用槽函数
    connect(ui->textBrowser, &QTextBrowser::anchorClicked, this, [=](const QUrl &url){
        QString nUrlInform = url.toString();
        /// ====== 新建工程
        if(0 == nUrlInform.compare("NewProject"))
        {
            if(NULL == m_createProject)
            {
                m_createProject = new OBNCreateProjectInterface(this);
                m_createProject->setWindowTitle(tr("新建工程"));
                connect(m_createProject, &OBNCreateProjectInterface::signalCreateProjectSuccess, this, &OBNWelcomeToTheInterface::setupCurrentProjectListFunc);
            }
            m_createProject->open();
        }
        /// ====== 编辑工程
        if(0 == nUrlInform.compare("EditProject"))
        {
            if(NULL == m_editProject)
            {
                m_editProject = new OBNEditPorjectInterface(this);
                m_editProject->setWindowTitle(tr("编辑工程"));
            }
            m_editProject->open();
        }
        /// ====== 删除工程
        if(0 == nUrlInform.compare("DeleteProject"))
        {
            if(NULL == m_deleteProject)
            {
                m_deleteProject = new OBNDeleteProjectInterface(this);
                m_deleteProject->setWindowTitle(tr("删除工程"));
                connect(m_deleteProject, &OBNDeleteProjectInterface::signalDeleteProjectSuccess, this, [=](){
                    setupCurrentProjectListFunc();
                });
            }
            m_deleteProject->open();
        }
    });

    /// ====== 点击”进入系统”按钮触发信号
    connect(ui->buttonEnterTheSystem, &QPushButton::clicked, this, [=](bool){
        /// ======
        if(0 == ui->comboBoxProject->count() || ui->comboBoxProject->currentText().isEmpty())
        {
            QMessageBox::information(this, tr("错误"), tr("请选择工区,如果没有请先创建工区！"), tr("确定"));
            return;
        }
        int languageText = ui->comboBoxLanguage->currentIndex();
        QString projectText  = ui->comboBoxProject->currentText();
        QStringList n_projectPathInformList = projectText.split("/");
        QString projectName = n_projectPathInformList.at(n_projectPathInformList.count()-1);
        emit signalEnterSystem(languageText, projectName, projectText);
    });
    /// ======
    connect(ui->comboBoxLanguage, SIGNAL(currentIndexChanged(const int &)), this, SLOT(slotFunctionToggleLanguageSelection(const int&)));
    /// ====== 读取语言设置配置文件,获取上次保存的语言配置,并设置语言
    ui->comboBoxLanguage->setCurrentIndex(AppGlobal::getInstance()->getCurrentLanguageMode());
}

OBNWelcomeToTheInterface::~OBNWelcomeToTheInterface()
{
    delete ui;
}

void OBNWelcomeToTheInterface::slotFunctionToggleLanguageSelection(const int & index)
{
    AppGlobal::getInstance()->setCurrentLanguageMode(index);
    qApp->removeTranslator(&m_translator);
    switch(index)
    {
    case 0:
        m_translator.load(":/translate/cn.qm");
        break;
    case 1:
        m_translator.load(":/translate/en.qm");
        break;
    default:
        break;
    }
    qApp->installTranslator(&m_translator);
    ui->retranslateUi(this);
}

/// ====== 读取工区信息文件,获取工区列表
void OBNWelcomeToTheInterface::setupCurrentProjectListFunc()
{
    /// ====== 清除当前工区信息列表
    ui->comboBoxProject->clear();

    /// ====== 读取工区信息列表文件
    QStringList nProjectInformList;

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
                    QString nJsonValue = iJson.value().toString();
                    nProjectInformList.append(nJsonValue);
                }
            }
            fileRead.close();
        }
    }
    /// ====== 设置工区列表信息到下拉菜单
    if(0 != nProjectInformList.count())
    {
        ui->comboBoxProject->addItems(nProjectInformList);
    }
}

