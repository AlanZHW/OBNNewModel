#include "abstractareadialog.h"

AbstractAreaDialog::AbstractAreaDialog(QWidget *parent)
    :QDialog(parent),m_AreaDatainfo(0),first_choose(true)
{
    createBaseDlg();
    m_updateOpt = ReplaceSps;
    this->resize(QSize(540,290));
}

AbstractAreaDialog::~AbstractAreaDialog()
{
    if(m_AreaDatainfo)
    {
        delete m_AreaDatainfo;
    }
}

void AbstractAreaDialog::setAreaOption(AreaOption option)
{
    m_areaOpt = option;
    if(option == CreateArea)
    {
        m_updateGrpBox->hide();
    }
    else
    {
        m_updateGrpBox->show();
    }
}
void AbstractAreaDialog::setProgressValue(const int &value)
{
    m_progressBar->setValue(value);
}

void AbstractAreaDialog::setOperateHint(const QString &hint)
{
    qDebug()<<"set hint:"<<hint;
    m_progressHintLbl->setText(hint);
}

void AbstractAreaDialog::setOptBtnText(const QString &text)
{    
    m_operateBtn->setText(text);
}

void AbstractAreaDialog::setAreaEditReadOnly(const bool &readOnly)
{
    m_areaNameEdt->setReadOnly(readOnly);
}

void AbstractAreaDialog::setAreaName(const QString &areaName)
{
    m_areaNameEdt->setText(areaName);
}

void AbstractAreaDialog::createBaseDlg()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    //Area name-----------------------
    QHBoxLayout  *areaNameLayout = new QHBoxLayout;
    QLabel    *areaNameLbl = new QLabel(tr("Area Name:"));  ///< Area Name
    m_areaNameEdt = new QLineEdit;
    m_areaNameEdt->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z_]+[a-zA-Z0-9_]+")));
    areaNameLayout->addWidget(areaNameLbl);
    areaNameLayout->addWidget(m_areaNameEdt);
    mainLayout->addLayout(areaNameLayout);

    //Select SPS Files---------------------------------------------
    QGroupBox *spsGrpBox = new QGroupBox("Select SPS Files");
    QGridLayout *grpLayout = new QGridLayout;
    grpLayout->setContentsMargins(0,4,0,4);
    grpLayout->setColumnStretch(1,1);

    QLabel    *RfileLbl = new QLabel("R File:");
    m_RfileEdt = new QLineEdit;
    QPushButton *RbrwBtn = new QPushButton("...");
    RbrwBtn->setProperty("type", "R");
    RbrwBtn->setMaximumWidth(36);
    grpLayout->addWidget(RfileLbl,0,0);
    grpLayout->addWidget(m_RfileEdt,0,1);
    grpLayout->addWidget(RbrwBtn,0,2);

    QLabel *SfileLbl = new QLabel("S File:");
    m_SfileEdt = new QLineEdit;
    QPushButton *SbrwBtn = new QPushButton("...");
    SbrwBtn->setProperty("type","S");
    SbrwBtn->setMaximumWidth(36);
    grpLayout->addWidget(SfileLbl,1,0);
    grpLayout->addWidget(m_SfileEdt,1,1);
    grpLayout->addWidget(SbrwBtn,1,2);

    QLabel *XfileLbl = new QLabel("X File:");
    m_XfileEdt = new QLineEdit;
    QPushButton *XbrwBtn = new QPushButton("...");
    XbrwBtn->setProperty("type","X");
    XbrwBtn->setMaximumWidth(36);
    grpLayout->addWidget(XfileLbl,2,0);
    grpLayout->addWidget(m_XfileEdt,2,1);
    grpLayout->addWidget(XbrwBtn,2,2);

    m_autoFileDectCbx = new QCheckBox("Auto File Detect",this);
    m_autoFileDectCbx->setChecked(true);
    grpLayout->addWidget(m_autoFileDectCbx,3,0,1,3,Qt::AlignLeft);

    spsGrpBox->setLayout(grpLayout);
    mainLayout->addWidget(spsGrpBox);

    m_updateGrpBox = new QGroupBox("Update Option",this);
    QHBoxLayout  *cheBoxLayout = new QHBoxLayout;

    QRadioButton *replaceRbx = new QRadioButton("Replace(Need S,R Files)");
    cheBoxLayout->addWidget(replaceRbx);
    replaceRbx->setChecked(true);

    QRadioButton *mergeRbx = new QRadioButton("Merge(Need S File)");
    cheBoxLayout->addWidget(mergeRbx);
    m_updateGrpBox->setLayout(cheBoxLayout);
    mainLayout->addWidget(m_updateGrpBox);
    m_updateGrpBox->hide();

    //ProgressBar --------------------------
    QFrame      *progressFr = new QFrame(this);
    QVBoxLayout *progressVlayout = new QVBoxLayout;
    m_progressHintLbl = new QLabel("                           ");
    //m_progressHintLbl->setMinimumWidth(120);
    m_progressHintLbl->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    progressVlayout->addWidget(m_progressHintLbl,1,Qt::AlignHCenter);
    m_progressBar = new QProgressBar;
    progressVlayout->addWidget(m_progressBar);
    progressVlayout->setContentsMargins(2,4,2,0);

    progressFr->setLayout(progressVlayout);
    progressFr->setFrameShape(QFrame::Box);

    mainLayout->addWidget(progressFr);

    //分割线------------------------------------
    QFrame *line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    mainLayout->addWidget(line);

    //buttons-------------------------------
    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addStretch(1);
    m_operateBtn = new QPushButton("operate");
    btnLayout->addWidget(m_operateBtn);
    btnLayout->addStretch(1);
    QPushButton *cancelBtn = new QPushButton("Cancel");
    btnLayout->addWidget(cancelBtn);
    btnLayout->addStretch(1);
    QPushButton *helpBtn = new QPushButton("Help");
    btnLayout->addWidget(helpBtn);
    btnLayout->addStretch(1);

    mainLayout->addLayout(btnLayout);

    this->setLayout(mainLayout);

    //signal - slots------------------------------------------
    connect(RbrwBtn,    SIGNAL(clicked(bool)),this,SLOT(slotBrowserSPSFile()));
    connect(SbrwBtn,    SIGNAL(clicked(bool)),this,SLOT(slotBrowserSPSFile()));
    connect(XbrwBtn,    SIGNAL(clicked(bool)),this,SLOT(slotBrowserSPSFile()));
    connect(m_operateBtn,SIGNAL(clicked(bool)),this,SLOT(slotOperate()));
    connect(cancelBtn,  SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(helpBtn,    SIGNAL(clicked(bool)),this,SLOT(slotHelp()));
    connect(replaceRbx, SIGNAL(clicked(bool)),this,SLOT(slotReplaceUpdate()));
    connect(mergeRbx,   SIGNAL(clicked(bool)),this,SLOT(slotMergeUpdate()));
}

void AbstractAreaDialog::slotBrowserSPSFile()
{
    QPushButton  *brwsBtn = static_cast<QPushButton *>(sender());
    QString brwFileType = brwsBtn->property("type").toString();

    QString Path;
    if(first_choose)
    {
        Path = QDir::homePath();
    }
    //(*.R* *.r*)格式
    QString filter = "SPS "+brwFileType+" Files(*."+brwFileType+"* *."+brwFileType.toLower()+"*)";
    QString fileName = QFileDialog::getOpenFileName(this,"Select SPS "+brwFileType+" File",Path,filter);
    if(fileName.isEmpty())
        return;
    first_choose = false;
    if(brwFileType == "R")
    {
        m_RfileEdt->setText(fileName);
    }
    if(brwFileType == "S")
    {
        m_SfileEdt->setText(fileName);
    }
    if(brwFileType == "X")
    {
        m_XfileEdt->setText(fileName);
    }
    if(m_autoFileDectCbx->isChecked())
    {
        autoDetectFile(brwFileType);
    }
}

void AbstractAreaDialog::autoDetectFile(const QString &type)
{
    //确定输入的文件
    QString inputFile;
    if(type == "R")
    {
        inputFile = rFileName();
    }
    if(type == "S")
    {
        inputFile = sFileName();
    }
    if(type == "X")
    {
        inputFile = xFileName();
    }

    /// ====== R file 查找
    int   dotIndex= inputFile.lastIndexOf(".");
    QChar typeChar = inputFile.at(dotIndex+1);
    if(type != "R")
    {
        QString rstFile = inputFile;
        if(typeChar.isLower())
        {
            rstFile.replace(dotIndex+1,1,'r');
        }
        else
        {
            rstFile.replace(dotIndex+1,1,'R');
        }
        QFile file(rstFile);
        if(file.exists())
        {
            m_RfileEdt->setText(rstFile);
        }
    }

    /// ====== S file 查找
    if(type != "S")
    {
        QString rstFile = inputFile;
        if(typeChar.isLower()){
            rstFile.replace(dotIndex+1,1,'s');
        }
        else{
            rstFile.replace(dotIndex+1,1,'S');
        }
        QFile file(rstFile);
        if(file.exists()){
            m_SfileEdt->setText(rstFile);
        }
    }

    /// ====== X file 查找
    if(type != "X")
    {
        QString rstFile = inputFile;
        if(typeChar.isLower())
        {
            rstFile.replace(dotIndex+1,1,'x');
        }
        else
        {
            rstFile.replace(dotIndex+1,1,'X');
        }
        QFile file(rstFile);
        if(file.exists())
        {
            m_XfileEdt->setText(rstFile);
        }
    }
}

void AbstractAreaDialog::slotOperate()
{
    m_spsFiles.clear();

    /// ====== 判断输入参数是否正确
    QString area_name = areaName();
    if(area_name.isEmpty())
    {
        QMessageBox::warning(this, tr("warning"), tr("Please input area name!"));
        return;
    }

    QString fileName  = rFileName();
    /// ====== Merge更新可以没有R文件
    if(!(m_areaOpt == UpdateArea && m_updateOpt == MergeSps)){

        if(fileName.isEmpty())
        {
            QMessageBox::warning(this,"warning","Please input R file!");
            return;
        }
    }
    m_spsFiles.append(fileName);

    fileName = sFileName();
    if(fileName.isEmpty())
    {
        QMessageBox::warning(this,"warning","Please input S file!");
        return;
    }
    m_spsFiles.append(fileName);

    /// ====== x 文件可选
    fileName = xFileName();
    m_spsFiles.append(fileName);

    /// ====== 执行run函数
    run();
}


void AbstractAreaDialog::slotReplaceUpdate()
{
    m_updateOpt = ReplaceSps;
}

void AbstractAreaDialog::slotMergeUpdate()
{
    m_updateOpt = MergeSps;
}

