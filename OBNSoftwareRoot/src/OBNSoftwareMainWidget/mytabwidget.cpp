#include "mytabwidget.h"

MyTabWidget::MyTabWidget(QWidget *parent)
{
    QDir bin_dir(QCoreApplication::applicationDirPath());
    bin_dir.cdUp();
    setAttribute(Qt::WA_StyledBackground);
    initTabBar();
}

MyTabWidget::~MyTabWidget()
{

}

int MyTabWidget::appendNormalPage(QWidget *page, QIcon pIcon)
{
    if(!page)
        return -1;
    //设置为调用close时释放
    page->setAttribute(Qt::WA_DeleteOnClose);
    //最后是添加到stackedWidget去了
    const int index=addTab(page, pIcon, page->windowTitle());
    //切换为当前新增页
    setCurrentIndex(index);
    return index;
}

void MyTabWidget::setProjectInfo(QString p_projectPath, QString p_projectName)
{
    m_projectPath = p_projectPath;
    m_projectName = p_projectName;
}

void MyTabWidget::slotTabCloseRequested(int index)
{
    if(indexValid(index))
    {
        QWidget* page = this->widget(index);
        if(!page || fixedPage.contains(page))
            return;
        removeTab(index);
        page->close();
    }
}

bool MyTabWidget::indexValid(int index) const
{
    if(index < 0 || index >= this->count())
        return false;
    return true;
}

void MyTabWidget::showEvent(QShowEvent *event)
{
    QTabWidget::showEvent(event);
    //初始化时把已有的设置为close释放
    for(int index=0; index<this->count(); index++)
    {
        QWidget *page=this->widget(index);
        if(page)
        {
            page->setAttribute(Qt::WA_DeleteOnClose);
        }
    }
}

void MyTabWidget::initTabBar()
{
    MyTabBar* bar = new MyTabBar(this);
    setTabBar(bar);

    connect(bar, &QTabBar::tabCloseRequested, this, &MyTabWidget::slotTabCloseRequested);
    //拖拽到外部-还未释放鼠标
    connect(bar,&MyTabBar::beginDragOut,this,[this,bar](int index)
    {
        if(!indexValid(index))
        {
            return;
        }
        QWidget *drag_tab = this->widget(index);
        //固定tab就不让拖出
        if(!drag_tab || fixedPage.contains(drag_tab))
        {
            return;
        }
        //把当前页作为快照拖拽
        //尺寸加了标题栏和边框
        QPixmap pixmap(drag_tab->size()+QSize(2,31));
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);
        if(painter.isActive())
        {
            //这里想做标题栏贴在内容之上
            //但是没法获取默认标题栏的图像啊，就随便画一个矩形框
            //如果设置了外部主题颜色，需要改下
            QRect title_rect{0,0,pixmap.width(),30};
            painter.fillRect(title_rect,Qt::white);
            painter.drawText(title_rect,Qt::AlignLeft|Qt::AlignVCenter,"  "+drag_tab->windowTitle());
            painter.drawRect(pixmap.rect().adjusted(0,0,-1,-1));
        }
        painter.end();
        drag_tab->render(&pixmap,QPoint(1,30));

        QMimeData *mime=new QMimeData;
        QDrag *drag=new QDrag(bar);
        drag->setMimeData(mime);
        drag->setPixmap(pixmap);
        drag->setHotSpot(QPoint(10,0));

        /// ====== 鼠标弹起后drag就释放了，这时候去判断是否拖拽到了外部
        connect(drag,&QDrag::destroyed,this,[=]
        {
            QPoint bar_point=bar->mapFromGlobal(QCursor::pos());
            //不在范围，拖出
            if(!bar->contentsRect().contains(bar_point))
            {
                popPage(drag_tab);
            }
        });
        drag->exec(Qt::MoveAction);
    });
}

void MyTabWidget::takeNormalPage(QWidget *page)
{
    if(!page)
        return;
    removeTab(indexOf(page));
}


void MyTabWidget::popPage(QWidget *page)
{
    QIcon nIcon;
    if(tr("观测系统") == page->windowTitle())
    {
        nIcon.addFile(":/image/OpenArea.png");
    }

    takeNormalPage(page);

    MyTabPopup *pop=new MyTabPopup(this);
    pop->setWindowIcon(nIcon);
    pop->setAttribute(Qt::WA_DeleteOnClose);
    pop->setContentWidget(page);
    pop->setWindowTitle(page->windowTitle());
    pop->resize(page->size());
    /// ====== 拖出来的位置有点偏移
    pop->move(QCursor::pos()-QPoint(10,10));

    /// ====== 判断独立窗口是否拖回tab
    connect(pop, &MyTabPopup::dragRelease,this,[=](const QPoint &pos)
    {
        const QPoint bar_pos = tabBar()->mapFromGlobal(pos);
        /// ====== 如果又拖回了tabbar范围内，就把widget取出来放回tab
        if(0 < bar_pos.x() && (0 < bar_pos.y() && 30 > bar_pos.y()))
        {
            QWidget *content = pop->getContentWidget();
            this->appendNormalPage(content, nIcon);
            pop->disconnect();
            /// ====== 关闭的时候会在原来的位置闪一下
            pop->close();
        }
    });
    pop->show();
    page->show();
    pop->activateWindow();
    pop->setFocus();
}

/// ====== 显示观测系统
void MyTabWidget::setLMGRDisplay(const QString& _projPath, const QString& _projName, const QString& _areaName)
{    
    LineManager *m_dislayArea = new LineManager(this);
    m_dislayArea->setWindowFlags(Qt::Widget);
//    m_dislayArea->setStyleSheet("QWidget{background-color:#EBEBEB;}");
    m_dislayArea->setAttribute(Qt::WA_DeleteOnClose);
    m_dislayArea->setCurrentProject(_projPath, _projName);
    m_dislayArea->slotOpenArea(_areaName);
    const int index = addTab(m_dislayArea, QIcon(":/image/OpenArea.png"), m_dislayArea->windowTitle());
    setCurrentIndex(index);
}

/// ====== 显示定位系统
void MyTabWidget::setGPositiSystem()
{
    GPositionSystem* nGPositionSystem = new GPositionSystem(this);
//    nGPositionSystem->setStyleSheet("QWidget{background-color:#EBEBEB;}");
    nGPositionSystem->setAttribute(Qt::WA_DeleteOnClose);
    const int index = addTab(nGPositionSystem, QIcon(":/image/OpenArea.png"), nGPositionSystem->windowTitle());
    setCurrentIndex(index);
}
/// ====== 显示SEGY数据
void MyTabWidget::setDisplaySEGY(QList<SegyFileHandle*> _pSegyFileHandle, int _maxTrace, int _startTrace, OpenFilesType _openFilesType)
{
    OBNDisplaySEGY* nDisplaySEGY = new OBNDisplaySEGY(this);
//    nDisplaySEGY->setStyleSheet("QWidget{background-color:#EBEBEB;}");
    nDisplaySEGY->setAttribute(Qt::WA_DeleteOnClose);
    nDisplaySEGY->setCurrentSEGYFileHandles(_pSegyFileHandle, _maxTrace, _startTrace, _openFilesType);
    const int index = addTab(nDisplaySEGY, QIcon(":/image/OpenArea.png"), nDisplaySEGY->windowTitle());
    setCurrentIndex(index);
}

/// ====== 显示LOG数据
void MyTabWidget::setDisplayLogInform()
{
    OBNLogVisuailzationDisplay* nDisplayLOG = new OBNLogVisuailzationDisplay(this);
//    nDisplayLOG->setStyleSheet("QWidget{background-color:#EBEBEB;}");
    nDisplayLOG->setAttribute(Qt::WA_DeleteOnClose);
    const int index = addTab(nDisplayLOG, QIcon(":/image/OpenArea.png"), nDisplayLOG->windowTitle());
    setCurrentIndex(index);
}

/// ======
void MyTabWidget::setStdManagerDiffTime()
{
    GobsDtMagerDiffTime* nDiffTime = new GobsDtMagerDiffTime(this);
//    nDiffTime->setStyleSheet("QWidget{background-color:#EBEBEB;}");
    nDiffTime->setAttribute(Qt::WA_DeleteOnClose);
    const int index = addTab(nDiffTime, QIcon(":/image/OpenArea.png"), nDiffTime->windowTitle());
    setCurrentIndex(index);
}

/// ======
void MyTabWidget::setRNMMainWindow()
{
    RNManager* nRNManager = new RNManager(this);
    nRNManager->setProjectInform(m_projectPath, m_projectName);
    nRNManager->setWindowFlags(Qt::Widget);
//    nRNManager->setStyleSheet("QWidget{background-color:#EBEBEB;}");
    nRNManager->setAttribute(Qt::WA_DeleteOnClose);
    const int index = addTab(nRNManager, QIcon(":/image/OpenArea.png"), nRNManager->windowTitle());
    setCurrentIndex(index);
}

/// ====== 显示OTA功能
void MyTabWidget::setOTAProgrameWindow()
{
    OBNLowerCumputerOTA* nOtaProgream = new OBNLowerCumputerOTA(this);
//    nOtaProgream->setStyleSheet("QWidget{background-color:#EBEBEB;}");
    nOtaProgream->setAttribute(Qt::WA_DeleteOnClose);
    const int index = addTab(nOtaProgream, QIcon(":/image/OpenArea.png"), nOtaProgream->windowTitle());
    setCurrentIndex(index);
}

/// ====== 显示实时波形显示功能
void MyTabWidget::setRealTimeWaveformDispProgrameWindow()
{
    OBNRealTimeWaveRoot* nRealTimeWaveformDispProgream = new OBNRealTimeWaveRoot(this);
//    nRealTimeWaveformDispProgream->setStyleSheet("QWidget{background-color:#EBEBEB;}");
    nRealTimeWaveformDispProgream->setAttribute(Qt::WA_DeleteOnClose);
    const int index = addTab(nRealTimeWaveformDispProgream, QIcon(":/image/OpenArea.png"), nRealTimeWaveformDispProgream->windowTitle());
    setCurrentIndex(index);
}

void MyTabWidget::setCalibrationDataDisplayProgrameWindow()
{
    OBNCalibrationDataDisplay* nRealTimeWaveformDispProgream = new OBNCalibrationDataDisplay(this);
//    nRealTimeWaveformDispProgream->setStyleSheet("QWidget{background-color:#EBEBEB;}");
    nRealTimeWaveformDispProgream->setAttribute(Qt::WA_DeleteOnClose);
    const int index = addTab(nRealTimeWaveformDispProgream, QIcon(":/image/OpenArea.png"), nRealTimeWaveformDispProgream->windowTitle());
    setCurrentIndex(index);
}

/// ====== 显示作业监控功能
void MyTabWidget::setJobMonitorProgreamWindow()
{
    OBNJobMonitorPrograme* nJobMonitorProgream = new OBNJobMonitorPrograme(this);
//    nJobMonitorProgream->setStyleSheet("QWidget{background-color:#EBEBEB;}");
    nJobMonitorProgream->setAttribute(Qt::WA_DeleteOnClose);
    const int index = addTab(nJobMonitorProgream, QIcon(":/image/OpenArea.png"), nJobMonitorProgream->windowTitle());
    setCurrentIndex(index);
}

