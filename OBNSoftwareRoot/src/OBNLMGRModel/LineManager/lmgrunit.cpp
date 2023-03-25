#include "lmgrunit.h"
#include "linemanager.h"


#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include <QProgressBar>
#include <QBoxLayout>
#include <QGroupBox>
#include <QFileDialog>
#include <QRadioButton>

#include <QMessageBox>


LmgrUnit::LmgrUnit()
{

}

//---------------------------------------
StationsInfoWg::StationsInfoWg(QWidget *parent)
    :QWidget(parent)
{

    initWg();
}

void StationsInfoWg::initWg()
{
    QFont font;
    int lbl_min_w = font.pointSize()*7;

    QHBoxLayout *infoLayout = new QHBoxLayout;
    QLabel *shotsNameLbl = new QLabel("Shots:");
    m_shotsLbl = new QLabel("");
    m_shotsLbl->setMinimumWidth(lbl_min_w);
    infoLayout->addWidget(shotsNameLbl);
    infoLayout->addWidget(m_shotsLbl);

    QLabel *recvsNameLbl = new QLabel("Nodes:");
    m_recvLbl = new QLabel("");
    m_recvLbl->setMinimumWidth(lbl_min_w);
    infoLayout->addWidget(recvsNameLbl);
    infoLayout->addWidget(m_recvLbl);

    QLabel *deployedNameLbl = new QLabel("Deployed(Recvs):");
    m_deployedLbl = new QLabel("");
    m_deployedLbl->setMinimumWidth(lbl_min_w);
    infoLayout->addWidget(deployedNameLbl);
    infoLayout->addWidget(m_deployedLbl);

    QLabel *pickedupNameLbl = new QLabel("Picked Up(Recvs):");
    m_pickedLbl = new QLabel("");
    m_pickedLbl->setMinimumWidth(lbl_min_w);
    infoLayout->addWidget(pickedupNameLbl);
    infoLayout->addWidget(m_pickedLbl);

    infoLayout->addStretch(1);
    infoLayout->setContentsMargins(6,4,6,4);

    this->setLayout(infoLayout);
}


void StationsInfoWg::setStationNum(const int &shots,const int recvs)
{
    m_shotsLbl->setText(QString::number(shots));
    m_recvLbl->setText(QString::number(recvs));
}


void StationsInfoWg::setRNInfoNum(const int &depolyed,const int &pickedUp)
{
    m_deployedLbl->setText(QString::number(depolyed));
    m_pickedLbl->setText(QString::number(pickedUp));
}

void StationsInfoWg::clearData()
{
    m_shotsLbl->clear();
    m_recvLbl->clear();
    m_deployedLbl->clear();
    m_pickedLbl->clear();
}


//-------------------------------
void LMGRMenuManager::createMenu(QMenuBar *menuBar,LineManager *lineManager)
{
    menuFile = new QMenu("File");
    //刷新工区
    menuFile->addAction(tr("Refresh Current Area"),lineManager,SLOT(slotUpdateCurrent()));
    menuFile->addAction("Close Current Area",lineManager,SLOT(slotCloseCurrent()),QKeySequence(tr("Ctrl+W")));
    menuFile->addSeparator();
    menuFile->addAction(tr("Exit"),lineManager,SLOT(slotExit()),QKeySequence(tr("Ctrl+Q")));
    menuBar->addMenu(menuFile);

    //Edit-----------------
    menuEdit = new QMenu("Edit");
    menuEdit->addAction("RN Deployments...",lineManager,SLOT(slotRNDeployments()));
    menuEdit->addAction("Assign RNs to Stations...",lineManager,SLOT(slotAssignRNDeployments()));
    menuEdit->addSeparator();
    menuEdit->addAction("Configure Deployments System...",lineManager,SLOT(slotConfigDeploySys()));

    dis_con_DpySysAct = new QAction("Connect/Dis Deployments System",menuEdit);
    dis_con_DpySysAct->setCheckable(true);
    connect(dis_con_DpySysAct,SIGNAL(triggered(bool)),lineManager,SLOT(slotDis_ConDeploySys(bool)));
    menuEdit->addAction(dis_con_DpySysAct);
    menuBar->addMenu(menuEdit);

    //View-----------------
    menuView = new QMenu("View");
    //Recv - Shots
    QAction *showRecvAct = new QAction("Show Recievers",menuView);
    showRecvAct->setCheckable(true);
    showRecvAct->setChecked(true);
    connect(showRecvAct,SIGNAL(triggered(bool)),lineManager,SLOT(slotShowRecvs(bool)));
    menuView->addAction(showRecvAct);

    QAction *showShotsAct = new QAction("Show Shots",menuView);
    showShotsAct->setCheckable(true);
    showShotsAct->setChecked(true);
    connect(showShotsAct,SIGNAL(triggered(bool)),lineManager,SLOT(slotShowShots(bool)));
    menuView->addAction(showShotsAct);
    menuView->addSeparator();

    //Recv - Shot lines
    QAction *showRecvlsAct = new QAction("Show Reciever Lines",menuView);
    showRecvlsAct->setCheckable(true);
    connect(showRecvlsAct,SIGNAL(triggered(bool)),lineManager,SLOT(slotShowRecvLines(bool)));
    menuView->addAction(showRecvlsAct);

    QAction *showShotlsAct = new QAction("Show Shot Lines",menuView);
    showShotlsAct->setCheckable(true);
    connect(showShotlsAct,SIGNAL(triggered(bool)),lineManager,SLOT(slotShowShotLines(bool)));
    menuView->addAction(showShotlsAct);
    menuView->addSeparator();

    //Shot - Recv Text
    QAction *showRecvTxtAct = new QAction("Show Reciever Text",menuView);
    showRecvTxtAct->setCheckable(true);
    connect(showRecvTxtAct,SIGNAL(triggered(bool)),lineManager,SLOT(slotShowRecvText(bool)));
    menuView->addAction(showRecvTxtAct);

    QAction *showShotTxtAct = new QAction("Show Shot Text",menuView);
    showShotTxtAct->setCheckable(true);
    connect(showShotTxtAct,SIGNAL(triggered(bool)),lineManager,SLOT(slotShowShotText(bool)));
    menuView->addAction(showShotTxtAct);

    menuView->addSeparator();
    //Preference
    menuView->addAction("Preference...",lineManager,SLOT(slotPreference()));
    menuBar->addMenu(menuView);

    //Help
    QMenu *menuHelp = new QMenu("Help");
    menuHelp->addAction("About...",lineManager,SLOT(slotAbout()),QKeySequence(tr("Ctrl+H")));
    menuBar->addMenu(menuHelp);

    //初始化菜单状态
    updateMenuStatus(false);
}

void LMGRMenuManager::updateMenuStatus(const bool &enable)
{
    if(m_enable == enable)
    {
        return;
    }
    m_enable = enable;
    //初始化菜单状态
    //File
    QList<QAction*> fileActoins = menuFile->actions();
    fileActoins.at(0)->setEnabled(enable);
    fileActoins.at(1)->setEnabled(enable);//update

    //Edit
    QList<QAction*> editActoins = menuEdit->actions();
    editActoins.at(0)->setEnabled(enable);//RN Deployments...

    //View
    QList<QAction*> viewActoins = menuView->actions();
    viewActoins.at(0)->setEnabled(enable);//Show Recvs
    viewActoins.at(1)->setEnabled(enable);//Show Shots
    //separator--
    viewActoins.at(3)->setEnabled(enable);//Show Recv Lines
    viewActoins.at(4)->setEnabled(enable);//Show Shots Lines
}

void LMGRMenuManager::setDeploySysConnected(const bool &connected)
{
    dis_con_DpySysAct->setChecked(connected);
}

/// ---------------------------------ToolManager
///
void LMGRToolManager::createToolBar(QToolBar *toolBar,LineManager *lineManager)
{
    //文件目录
    QString    m_Path = QCoreApplication::applicationDirPath();

    m_toolBar = toolBar;

    toolBar->addAction(QIcon(m_Path+"/Image/close.png"),"Close Area",lineManager,SLOT(slotCloseCurrent()));
    toolBar->addSeparator();
    toolBar->addAction(QIcon(m_Path+"/Image/update.png"),"Update Current Area",lineManager,SLOT(slotUpdateCurrent()));
    toolBar->addSeparator();
    toolBar->addAction(QIcon(m_Path+"/Image/zoom_in.png"),  "Zoom In(5%)",lineManager,SLOT(slotZoomIn()));
    toolBar->addAction(QIcon(m_Path+"/Image/zoom_out.png"), "Zoom Out(5%)",lineManager,SLOT(slotZoomOut()));
    toolBar->addAction(QIcon(m_Path+"/Image/zoom_in_full.png"),"Zoom In Fully",lineManager,SLOT(slotZoomInFull()));
    toolBar->addAction(QIcon(m_Path+"/Image/zoom_out_full.png"),"Zoom Out Fully",lineManager,SLOT(slotZoomOutFull()));
    toolBar->addSeparator();
    toolBar->addAction(QIcon(m_Path+"/Image/list_item.png"),"Show RN Deployments",lineManager,SLOT(slotRNDeployments()));
    //初始化工具栏状态
    updateToolBarStatus(false);
}

void LMGRToolManager::updateToolBarStatus(const bool &enable)
{
    if(m_enable == enable)
        return;
    m_enable = enable;
    QList<QAction *> toolActions = m_toolBar->actions();
    toolActions.at(0)->setEnabled(enable); //Close
    toolActions.at(2)->setEnabled(enable); //Update
    toolActions.at(9)->setEnabled(enable); //RN Deployments
}

/*AbstractAreaList------------------------------*/
AreaListDlg::AreaListDlg(QWidget *parent)
    :QDialog(parent),m_areaOpt(Open_Area)
{
    this->setWindowFlags(Qt::Dialog);

    initDlg();

    if(m_areaOpt == Open_Area)
        this->setWindowTitle("Select Existing Area to open");
    else if(m_areaOpt == Delete_Area)
        this->setWindowTitle("Select Existing Area to delete");
}

void AreaListDlg::setAreaOpt(const AreaOpt &opt)
{
    m_areaOpt = opt;
    if(m_areaOpt == Open_Area)
        this->setWindowTitle("Select Existing Area to open");
    else if(m_areaOpt == Delete_Area)
        this->setWindowTitle("Select Existing Area to delete");
}

AreaListDlg::~AreaListDlg()
{
}

void AreaListDlg::initDlg()
{
    QVBoxLayout *vLayout = new QVBoxLayout;

    QHBoxLayout  *lblLayout = new QHBoxLayout;

    QLabel       *areaname_lbl= new QLabel("Area Name:");
    lblLayout->addWidget(areaname_lbl);
    lblLayout->addStretch(1);
    vLayout->addLayout(lblLayout);

    m_listWidget = new QListWidget(this);
    m_listWidget->setWindowTitle("area Names");
    vLayout->addWidget(m_listWidget);

    QHBoxLayout *hLayout = new QHBoxLayout;
    QPushButton *okBtn = new QPushButton("Ok");
    QPushButton *cancelBtn = new QPushButton("Cancel");
    hLayout->addStretch(1);
    hLayout->addWidget(okBtn);
    hLayout->addWidget(cancelBtn);

    vLayout->addLayout(hLayout);

    connect(okBtn,SIGNAL(clicked(bool)),this,SLOT(slotOk()));
    connect(cancelBtn,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(m_listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(slotOk()));
    this->setLayout(vLayout);
    this->resize(300,400);
}

void AreaListDlg::updateAreaList()
{
    //项目文件--------------------------
    QString projFile = m_projInfo.ProjectPath + Dir_Separator + m_projInfo.ProjectName+Project_File_Suffix;
    QStringList  areaList= Area::areasFromProject(projFile);

    m_listWidget->clear();
    for(int i=0;i<areaList.size();i++)
        m_listWidget->addItem(new QListWidgetItem(areaList.at(i)));
}

void AreaListDlg::showAreaList()
{
    //项目文件--
    QString projFile = m_projInfo.ProjectPath + Dir_Separator + m_projInfo.ProjectName+Project_File_Suffix;
    QStringList  areaList= Area::areasFromProject(projFile);

    m_listWidget->clear();
    for(int i=0;i<areaList.size();i++)
        m_listWidget->addItem(new QListWidgetItem(areaList.at(i)));

    this->exec();
}


void AreaListDlg::slotOk()
{
    QListWidgetItem *item = m_listWidget->currentItem();
    if(!item)
        return;
    QString areaName = item->text();

    if(m_areaOpt == Open_Area){
        emit signalOpenArea(areaName);
        this->close();
    }
    else if(m_areaOpt == Delete_Area){
        emit signalDeleteArea(areaName);
    }
}

//----------------------------------------------------
PreferenceDlg::PreferenceDlg(QWidget *parent)
    :QDialog(parent)
{
    this->setWindowTitle("Color Preference");
    initDlg();
}

void PreferenceDlg::initDlg()
{
    m_btnGroup   = new QButtonGroup(this);
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QFrame      *buttonsFr = new QFrame(this);
    buttonsFr->setFrameShape(QFrame::Box);
    QGridLayout *buttonsLayout = new QGridLayout;

    //backGroud----
    QLabel       *bkColorLbl = new QLabel("BackGroud Color",this);
    m_bkColorBtn = new ColorPickButton(this);
    m_bkColorBtn->setColor(Qt::black);
    m_bkColorBtn->setId(Backdroud_Color);
    buttonsLayout->addWidget(bkColorLbl,0,0);
    buttonsLayout->addWidget(m_bkColorBtn,0,1);
    m_colorMap.insert(Backdroud_Color,Qt::black);
    m_btnGroup->addButton(m_bkColorBtn,Backdroud_Color);


    //Shot
    QLabel *shotColorLbl = new QLabel("Shot Color",this);
    m_shotColorBtn = new ColorPickButton(this);
    m_shotColorBtn->setColor(Qt::red);
    m_shotColorBtn->setId(Shot_Color);
    buttonsLayout->addWidget(shotColorLbl,1,0);
    buttonsLayout->addWidget(m_shotColorBtn,1,1);
    m_colorMap.insert(Shot_Color,Qt::red);
    m_btnGroup->addButton(m_shotColorBtn,Shot_Color);

    //Fired Shot
    QLabel *firedShotColorLbl = new QLabel("Fired Shot Color",this);
    m_firedShotColorBtn = new ColorPickButton(this);
    m_firedShotColorBtn->setColor(Qt::cyan);
    m_firedShotColorBtn->setId(Fired_Shot_Color);
    buttonsLayout->addWidget(firedShotColorLbl,2,0);
    buttonsLayout->addWidget(m_firedShotColorBtn,2,1);
    m_colorMap.insert(Fired_Shot_Color,Qt::cyan);
    m_btnGroup->addButton(m_firedShotColorBtn,Fired_Shot_Color);

    //recv
    QLabel *recvColorLbl = new QLabel("Reciever Color",this);
    m_recvColorBtn = new ColorPickButton(this);
    m_recvColorBtn->setColor(Qt::white);
    m_recvColorBtn->setId(Recv_Color);
    buttonsLayout->addWidget(recvColorLbl,3,0);
    buttonsLayout->addWidget(m_recvColorBtn,3,1);
    m_colorMap.insert(Recv_Color,Qt::white);
    m_btnGroup->addButton(m_recvColorBtn,Recv_Color);

    //shotLine
    QLabel *shotLineColorLbl = new QLabel("Shot Line Color",this);
    m_shotLineColorBtn = new ColorPickButton(this);
    m_shotLineColorBtn->setColor(Qt::cyan);
    m_shotLineColorBtn->setId(Shot_Line_Color);
    buttonsLayout->addWidget(shotLineColorLbl,4,0);
    buttonsLayout->addWidget(m_shotLineColorBtn,4,1);
    m_colorMap.insert(Shot_Line_Color,Qt::cyan);
    m_btnGroup->addButton(m_shotLineColorBtn,Shot_Line_Color);
    //recvLine
    QLabel *recvLineColorLbl = new QLabel("Reciever Line Color",this);
    m_recvLineColorBtn = new ColorPickButton(this);
    m_recvLineColorBtn->setColor(Qt::magenta);
    m_recvLineColorBtn->setId(Recv_Line_Color);
    buttonsLayout->addWidget(recvLineColorLbl,5,0);
    buttonsLayout->addWidget(m_recvLineColorBtn,5,1);
    m_colorMap.insert(Recv_Line_Color,Qt::magenta);
    m_btnGroup->addButton(m_recvLineColorBtn,Recv_Line_Color);
    //Legend
    QLabel *legendColorLbl = new QLabel("Legend Color",this);
    m_legendColorBtn = new ColorPickButton(this);
    m_legendColorBtn->setColor(Qt::white);
    m_legendColorBtn->setId(Legend_Color);
    buttonsLayout->addWidget(legendColorLbl,6,0);
    buttonsLayout->addWidget(m_legendColorBtn,6,1);
    m_colorMap.insert(Legend_Color,Qt::white);
    m_btnGroup->addButton(m_legendColorBtn,Legend_Color);
    //Deployed Station
    QLabel *deployedColorLbl = new QLabel("Deployed Reciever Color",this);
    m_deployedColorBtn = new ColorPickButton(this);
    m_deployedColorBtn->setColor(Qt::yellow);
    m_deployedColorBtn->setId(Deployed_Recv_Color);
    buttonsLayout->addWidget(deployedColorLbl,7,0);
    buttonsLayout->addWidget(m_deployedColorBtn,7,1);
    m_colorMap.insert(Deployed_Recv_Color,Qt::yellow);
    m_btnGroup->addButton(m_deployedColorBtn,Deployed_Recv_Color);
    //Picked Up
    QLabel *pickedColorLbl = new QLabel("Picked Up Reciever Color          ",this);
    m_pickedColorBtn = new ColorPickButton(this);
    m_pickedColorBtn->setColor(Qt::blue);
    m_pickedColorBtn->setId(PickedUp_Recv_Color);
    buttonsLayout->addWidget(pickedColorLbl,8,0);
    buttonsLayout->addWidget(m_pickedColorBtn,8,1);
    m_colorMap.insert(PickedUp_Recv_Color,Qt::blue);
    m_btnGroup->addButton(m_pickedColorBtn,PickedUp_Recv_Color);

    //Download gobs
    QLabel *downloadedColorLbl = new QLabel("Downloaded Reciever Color          ",this);
    m_downloadedColorBtn = new ColorPickButton(this);
    m_downloadedColorBtn->setColor(Qt::green);
    m_downloadedColorBtn->setId(Downloaded_Recv_Color);
    buttonsLayout->addWidget(downloadedColorLbl,9,0);
    buttonsLayout->addWidget(m_downloadedColorBtn,9,1);
    m_colorMap.insert(Downloaded_Recv_Color,Qt::green);
    m_btnGroup->addButton(m_downloadedColorBtn,Downloaded_Recv_Color);

    //shot Station Text
    QLabel *shotTextColorLbl = new QLabel("Shot Text Color",this);
    m_shotTextColorBtn = new ColorPickButton(this);
    m_shotTextColorBtn->setColor(QColor(255,153,0));
    m_shotTextColorBtn->setId(Shot_Text_Color);
    buttonsLayout->addWidget(shotTextColorLbl,10,0);
    buttonsLayout->addWidget(m_shotTextColorBtn,10,1);
    m_colorMap.insert(Shot_Text_Color,QColor(255,153,0));
    m_btnGroup->addButton(m_pickedColorBtn,Shot_Text_Color);

    //Reciever Station Text
    QLabel *recvTextColorLbl = new QLabel("Shot Text Color",this);
    m_recvTextColorBtn = new ColorPickButton(this);
    m_recvTextColorBtn->setColor(QColor(0,255,51));
    m_recvTextColorBtn->setId(Recv_Text_Color);
    buttonsLayout->addWidget(recvTextColorLbl,11,0);
    buttonsLayout->addWidget(m_recvTextColorBtn,11,1);
    m_colorMap.insert(Recv_Text_Color,QColor(0,255,51));
    m_btnGroup->addButton(m_recvTextColorBtn,Recv_Text_Color);

    buttonsFr->setLayout(buttonsLayout);
    mainLayout->addWidget(buttonsFr);

    QFrame  *hLine1 = new QFrame(this);
    hLine1->setFrameShape(QFrame::HLine);
    hLine1->setFrameShadow(QFrame::Sunken);
    hLine1->setLineWidth(2);
    mainLayout->addWidget(hLine1);

    QFrame   *pointSizeFr = new QFrame(this);
    mainLayout->addWidget(pointSizeFr);


    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addStretch(1);
    QPushButton *okBtn = new QPushButton("Ok");
    btnLayout->addWidget(okBtn);

    btnLayout->addStretch(1);
    QPushButton *cancelBtn = new QPushButton("Cancel");
    btnLayout->addWidget(cancelBtn);
    btnLayout->addStretch(1);

    mainLayout->addLayout(btnLayout);

    this->setLayout(mainLayout);

    connect(okBtn,SIGNAL(clicked(bool)),this,SLOT(slotOkBtn()));
    connect(cancelBtn,SIGNAL(clicked(bool)),this,SLOT(slotCancelBtn()));

    connect(m_bkColorBtn,SIGNAL(colorChanged(int,QColor)),SIGNAL(colorChanged(int,QColor)));
    connect(m_shotColorBtn,SIGNAL(colorChanged(int,QColor)),SIGNAL(colorChanged(int,QColor)));
    connect(m_firedShotColorBtn,SIGNAL(colorChanged(int,QColor)),SIGNAL(colorChanged(int,QColor)));
    connect(m_recvColorBtn,SIGNAL(colorChanged(int,QColor)),SIGNAL(colorChanged(int,QColor)));
    connect(m_shotLineColorBtn,SIGNAL(colorChanged(int,QColor)),SIGNAL(colorChanged(int,QColor)));
    connect(m_recvLineColorBtn,SIGNAL(colorChanged(int,QColor)),SIGNAL(colorChanged(int,QColor)));
    connect(m_legendColorBtn,SIGNAL(colorChanged(int,QColor)),SIGNAL(colorChanged(int,QColor)));
    connect(m_deployedColorBtn,SIGNAL(colorChanged(int,QColor)),SIGNAL(colorChanged(int,QColor)));
    connect(m_pickedColorBtn,SIGNAL(colorChanged(int,QColor)),SIGNAL(colorChanged(int,QColor)));
    connect(m_downloadedColorBtn,SIGNAL(colorChanged(int,QColor)),SIGNAL(colorChanged(int,QColor)));
    connect(m_shotTextColorBtn,SIGNAL(colorChanged(int,QColor)),SIGNAL(colorChanged(int,QColor)));
    connect(m_recvTextColorBtn,SIGNAL(colorChanged(int,QColor)),SIGNAL(colorChanged(int,QColor)));
}


void PreferenceDlg::slotOkBtn()
{
    //刷新值
    m_colorMap.insert(m_bkColorBtn->id(),m_bkColorBtn->color());
    m_colorMap.insert(m_shotColorBtn->id(),m_shotColorBtn->color());
    m_colorMap.insert(m_recvColorBtn->id(),m_recvColorBtn->color());
    m_colorMap.insert(m_shotLineColorBtn->id(),m_shotLineColorBtn->color());
    m_colorMap.insert(m_recvLineColorBtn->id(),m_recvLineColorBtn->color());
    m_colorMap.insert(m_legendColorBtn->id(),m_legendColorBtn->color());
    m_colorMap.insert(m_deployedColorBtn->id(),m_deployedColorBtn->color());
    m_colorMap.insert(m_pickedColorBtn->id(),m_pickedColorBtn->color());
    m_colorMap.insert(m_shotTextColorBtn->id(),m_shotTextColorBtn->color());
    m_colorMap.insert(m_recvTextColorBtn->id(),m_recvTextColorBtn->color());

    this->close();
}

void PreferenceDlg::slotCancelBtn()
{
    //使用现有的值刷新设置
    emit colorMapChanged(m_colorMap);

    this->close();
}
