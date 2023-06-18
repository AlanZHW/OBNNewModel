#include "opensegydlg.h"

#include "ui_opensegydlg.h"

//OpenSegyDlg---------------------------------
OpenSegyDlg::OpenSegyDlg(QWidget *parent)
    :QDialog(parent)
    ,ui(new Ui::OpenSegyDlg)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("显示SEGY文件"));
    m_fileDetailDlg  = new FileDetailDlg(this);
    m_OpenFilesType  = One_Component;//默认打开一个分量文件显示
    ui->maxShowTraceSpx->setRange(1,INT_MAX);
    ui->maxShowTraceSpx->setValue(500);
    ui->startTraceSpx->setRange(1,INT_MAX);
    ui->startTraceSpx->setValue(1);

    m_maxShowTraces = 500;
    ui->FileExpandWg->hide();
    ui->label->setText("File:");

    m_brwserBtnGrp  = new QButtonGroup(this);
    m_brwserBtnGrp->addButton(ui->brwserBtn,0);
    m_brwserBtnGrp->addButton(ui->brwserBtn_2,1);
    m_brwserBtnGrp->addButton(ui->brwserBtn_3,2);
    m_brwserBtnGrp->addButton(ui->brwserBtn_4,3);

    m_fileNameEdits.append(ui->fileNameEdit);
    m_fileNameEdits.append(ui->fileNameEdit_2);
    m_fileNameEdits.append(ui->fileNameEdit_3);
    m_fileNameEdits.append(ui->fileNameEdit_4);
    connect(m_brwserBtnGrp,SIGNAL(buttonClicked(int)),this,SLOT(slotBrwBtnClicked(int)));

    this->setFixedHeight(500);
}

OpenSegyDlg::~OpenSegyDlg()
{
    //如果当前有打开文件则关闭文件-----
    if(m_segyFileHandles.size()>0)
    {
        int ok = -1;
        for(int i=0;i<m_segyFileHandles.size();i++)
            gobs_close_segy_func(m_segyFileHandles[i]->openTrace,&ok);
    }
    qDeleteAll(m_segyFileHandles);
}

void OpenSegyDlg::slotBrwBtnClicked(int id)
{
    if(m_currentPath.isEmpty())
        m_currentPath = QDir::currentPath();

    //打开文件系统选择文件
    QString fileName = QFileDialog::getOpenFileName(this,tr("选择要打开的文件"), m_currentPath, tr("Segy(*.segy)"));
    if(fileName.isEmpty())
    {
        return;
    }
    m_currentPath = QFileInfo(fileName).filePath();

    //一分量
    QStringList m_fileList;
    if(m_OpenFilesType == One_Component)
    {
        m_fileNameEdits[id]->setText(fileName);
        m_fileList<<fileName;
        m_fileNameEdits[1]->clear();
        m_fileNameEdits[2]->clear();
        m_fileNameEdits[3]->clear();
    }
    else if(m_OpenFilesType == Four_Component)
    {
        //四分量，根据选择文件判断查找其他文件，保证文件存在并且正确
        QStringList componentSuffixs(QStringList()<<"bhx.segy"<<"bhy.segy"<<"bhz.segy"<<"hyd.segy");
        QList<int> fileIndex(QList<int>()<<0<<1<<2<<3);
        int idx = componentSuffixs.indexOf(fileName.right(8));
        if(idx != id)
        {
            QString inform = tr("需要输入数据") + componentSuffixs[idx] + "文件.";
            QMessageBox::warning(this, tr("警告"), inform, tr("确定"));
            return;
        }
        m_fileNameEdits[fileIndex[idx]]->setText(fileName);
        fileIndex.removeAt(idx);
        //设置其他文件，需要每个分量文件都存在才能打开显示
        QString prefixName = fileName;
        prefixName.chop(8);
        bool file_ok = true;
        for(int i=0;i<fileIndex.size();i++)
        {
            fileName = prefixName+componentSuffixs[fileIndex[i]];
            if(!QFile(fileName).exists())
            {
                m_fileNameEdits[fileIndex[i]]->clear();
                file_ok  = false;
            }
            else
            {
                m_fileNameEdits[fileIndex[i]]->setText(fileName);
            }
        }
        //文件没有问题，打开文件
        if(!file_ok) return;
        for(int i =0;i<m_fileNameEdits.size();i++)
        {
            m_fileList.append(m_fileNameEdits[i]->text().trimmed());
        }
    }
    //打开文件，获取基本信息
    if(!openSegyFile(m_fileList))
    {
        QMessageBox::warning(this, tr("打开文件"), tr("打开文件失败,请检查!"), tr("确定"));
    }
}

bool OpenSegyDlg::openSegyFile(const QStringList &files)
{
    //打开多个文件
    qDebug()<<"open files:"<<files;
    //打开文件获取信息
    int mode = Read_Only;
    int ok = -1;
    //打开所有分量文件
    QList<SegyFileHandle *> segyFileHandles;
    for(int i=0;i<files.size();i++)
    {
        char *binary3200 = new char[3200];
        BinaryHead *binaryhead = new BinaryHead;
        SegyInfo   *segyInfo   = new SegyInfo;
        OpenTrace *openTrace = gobs_open_segy_func(files[i].toLatin1().data(),&mode,binary3200,binaryhead,segyInfo,&ok);
        qDebug()<<"open segy file,ok="<<ok;
        if(ok != 0)
        {
            delete[] binary3200;
            delete   binaryhead;
            delete   segyInfo;
            qDeleteAll(segyFileHandles);
            segyFileHandles.clear();
            return false;
        }
        //2 保存文件信息
        ui->nsEdit->setText(QString::number(segyInfo->ns));
        ui->sampleInterEdit->setText(QString::number(segyInfo->sampleInterval));
        ui->nTraceEdit->setText(QString::number(segyInfo->traces));
        ui->maxShowTraceSpx->setRange(1,segyInfo->traces);
        ui->startTraceSpx->setRange(1,segyInfo->traces);

        SegyFileHandle *segyFileHandle = new SegyFileHandle;
        //更新当前文件信息
        segyFileHandle->fileName   = files[i];
        segyFileHandle->binary3200 = binary3200;
        segyFileHandle->binaryhead = binaryhead;
        segyFileHandle->segyInfo   = segyInfo;
        segyFileHandle->openTrace  = openTrace;

        segyFileHandles.append(segyFileHandle);
    }

    //打开完成，关闭之前打开的文件
    for(int i=0;i<m_segyFileHandles.size();i++)
    {
        //打开成功，需要关闭上一个打开的文件
        if(m_segyFileHandles[i]->openTrace)
        {
            gobs_close_segy_func(m_segyFileHandles[i]->openTrace,&ok);
        }
    }
    qDeleteAll(m_segyFileHandles);

    m_segyFileHandles = segyFileHandles;

    //保存路径
    m_currentPath = QFileInfo(files[0]).path();
    //文件信息对话框显示信息
    m_fileDetailDlg->setSegyFileInfo(m_segyFileHandles[0]->binary3200,m_segyFileHandles[0]->binaryhead,m_segyFileHandles[0]->segyInfo);

    return true;
}

bool OpenSegyDlg::getFileList(QStringList &fileList)
{
    if(m_OpenFilesType == One_Component)
    {
        if(m_fileNameEdits[0]->text().trimmed().isEmpty())
        {
            return false;
        }
        fileList.append(m_fileNameEdits[0]->text().trimmed());
    }
    else
    {
        for(int i=0;i<4;i++)
        {
            if(m_fileNameEdits[i]->text().trimmed().isEmpty())
            {
                return false;
            }
            fileList.append(m_fileNameEdits[i]->text().trimmed());
        }
    }
    return true;
}

void OpenSegyDlg::on_okBtn_clicked()
{
    QStringList fileList;
    //获取文件
    if(!getFileList(fileList))
    {
        return;
    }
    bool opened = true;
    //分量改变
    if(fileList.size()!=m_segyFileHandles.size())
    {
        opened = false;
    }
    else
    {
        //判断每个分量文件是否相等
        for(int i=0;i<m_segyFileHandles.size();i++)
        {
            if(m_segyFileHandles[i]->fileName != fileList[i])
            {
                opened  = false;
                break;
            }
        }
    }
    if(!opened)
    {
        //打开文件
        if(!openSegyFile(fileList))
        {
            QMessageBox::warning(this,"Open File","Open File Error.");
            return;
        }
    }
    m_maxShowTraces = ui->maxShowTraceSpx->value();
    //读取数据时候从0开始
    m_startTrace    = ui->startTraceSpx->value()-1;
    //发送文件信息给主界面
    emit signalOpenedFile(m_segyFileHandles, m_maxShowTraces, m_startTrace, m_OpenFilesType);
    this->close();
}

void OpenSegyDlg::on_cancelBtn_clicked()
{
    this->close();
}

void OpenSegyDlg::on_detailBtn_clicked()
{
    m_fileDetailDlg->show();
}

void OpenSegyDlg::on_OneComRbtn_clicked()
{
    if(m_OpenFilesType==One_Component)
    {
        return;
    }
    m_OpenFilesType = One_Component;
    ui->label->setText(tr("文件:"));
    int decHeight = ui->FileExpandWg->height();
    ui->FileExpandWg->hide();
    ui->groupBox_3->resize(ui->groupBox_3->width(), ui->groupBox_3->height() -decHeight);

    this->setFixedHeight(500);
}

void OpenSegyDlg::on_FourComRbtn_clicked()
{
    if(m_OpenFilesType==Four_Component)
    {
        return;
    }
    m_OpenFilesType = Four_Component;
    ui->label->setText(tr("文件(bhx):"));
    ui->FileExpandWg->show();
    this->setFixedHeight(589);
}
