#include "exportsegydlg.h"
#include "ui_exportsegydlg.h"

ExportSegyDlg::ExportSegyDlg(QWidget *parent)
    :QDialog(parent)
    ,ui(new Ui::ExportSegyDlg)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("导出SEGY"));

    //设置validator
    ui->traceLenEdit->setValidator(new QIntValidator(100,100000,this));

    m_shotLineDlg = new ShotLineDlg(this);
    m_areaDataInfo = 0;
    ui->textHeaderFrame->setFrameShape(QFrame::NoFrame);
}

ExportSegyDlg::~ExportSegyDlg()
{
    if(m_areaDataInfo)
    {
        m_areaDataInfo->clearData();
        delete m_areaDataInfo;
        m_areaDataInfo = 0;
    }
}

void ExportSegyDlg::setProjectInfo(const ProjectInfo & projInfo)
{
    m_projInfo = projInfo;
    m_exportParameters.projectPath = m_projInfo.ProjectPath;
    m_exportParameters.projectName = m_projInfo.ProjectName;
    initByProject();
}

void ExportSegyDlg::initByProject()
{
    //初始化工区列表
    QString projFile = m_projInfo.ProjectPath+Dir_Separator+m_projInfo.ProjectName+Project_File_Suffix;
    QStringList areaList = Area::areasFromProject(projFile);
    qDebug() << __FILE__ << "\t" << __LINE__ << "\t areaList = " << areaList;
    if(0 != areaList.count())
    {
        ui->areasCbx->addItems(areaList);
    }
}

void ExportSegyDlg::updateScopeInfo()
{
    if(!m_areaDataInfo)
    {
        return;
    }

    /// ====== 选中输出炮道集
    if(ui->shotRbtn->isChecked())
    {
        StationInfo *shotStationInfo = m_areaDataInfo->shotStationInfo;

        //line
        ui->fromLineSpx->setRange(1,shotStationInfo->lineNum);
        ui->toLineSpx->setRange(1,shotStationInfo->lineNum);
        ui->fromLineSpx->setValue(1);
        ui->toLineSpx->setValue(shotStationInfo->lineNum);

        //station，计算站点最多的线
        int max_staNum = 0;
        for(int i =0;i<shotStationInfo->lineNum;i++)
        {
            max_staNum = max_staNum < shotStationInfo->staLines[i].staNum ? shotStationInfo->staLines[i].staNum : max_staNum;
        }
        ui->fromStaSpx->setRange(1,max_staNum);
        ui->toStaSpx->setRange(1,max_staNum);
        ui->fromStaSpx->setValue(1);
        ui->toStaSpx->setValue(max_staNum);
    }

    /// ======选择输出检波点道集
    if(ui->recvRbtn->isChecked())
    {
        StationInfo *recvStationInfo = m_areaDataInfo->recvStationInfo;

        /// ====== 获取线最小值和最大值,以及炮最小值和最大值
        float lineMin = __FLT_MAX__, lineMax = __FLT_MIN__;
        int   staMin  = INT_MAX, staMax  = INT_MIN;

        for(int iLine = 0; iLine < recvStationInfo->lineNum; iLine ++)
        {
            lineMin = qMin(lineMin, recvStationInfo->staLines[iLine].line);
            lineMax = qMax(lineMax, recvStationInfo->staLines[iLine].line);

            for(int iStation = 0; iStation < recvStationInfo->staLines[iLine].staNum; iStation ++)
            {
                staMin = qMin(staMin, recvStationInfo->staLines[iLine].stations[iStation].sp);
                staMax = qMax(staMax, recvStationInfo->staLines[iLine].stations[iStation].sp);
            }
        }
        ui->fromLineSpx->setRange(lineMin, lineMax);
        ui->fromLineSpx->setValue(lineMin);
        ui->toLineSpx->setRange(lineMin,   lineMax);
        ui->toLineSpx->setValue(lineMax);

        ui->fromStaSpx->setRange(staMin, staMax);
        ui->fromStaSpx->setValue(staMin);
        ui->toStaSpx->setRange(staMin, staMax);
        ui->toStaSpx->setValue(staMax);
    }
}


void ExportSegyDlg::on_CloseBtn_clicked()
{
    this->close();
}


void ExportSegyDlg::on_ShotLineBrwser_clicked()
{
    if(!m_shotLineDlg->shotLineFiles().isEmpty())
    {
        m_shotLineDlg->show();
    }
    /// ======
    QStringList shotlineFiles = QFileDialog::getOpenFileNames(this,"Select ShotLine Files", QDir::currentPath());
    if(shotlineFiles.isEmpty())
    {
        return;
    }
    shotlineFiles.sort();
    m_shotLineDlg->setShotLineFiles(shotlineFiles);
    m_shotLineDlg->show();
}

void ExportSegyDlg::on_areasCbx_currentIndexChanged(const QString &arg1)
{
    //根据area 工区，读取工区炮检点信息，初始化选择范围
    QString areaName = arg1;

    QStringList spsfiles = Area::spsFiles(m_projInfo,areaName);
    if(spsfiles.size()<2)
    {
        QMessageBox::warning(this,"waring","Current area sps files error.");
        return;
    }
    if(m_areaDataInfo)
    {
        m_areaDataInfo->clearData();
        delete m_areaDataInfo;
    }
    QString errString;
    m_areaDataInfo =  new AreaDataInfo;
    int ok = gobs_sps_files_SR_read(spsfiles,m_areaDataInfo, &errString);
    if(ok!=0)
    {
        QMessageBox::critical(this, tr("错误"), QString("读取Area-SPS文件:%1").arg(errString));
        return;
    }
    //设置最大范围
    updateScopeInfo();
}

void ExportSegyDlg::on_recvRbtn_clicked(bool checked)
{
    //共检波点
    if(checked)
    {
        ui->ScopeGbx->setTitle(tr("接收线范围"));    ///< Reciever Scope
        ui->lineLbl->setText(tr("接收线号"));        ///< Reciever Line
        ui->stationLbl->setText(tr("接收站点号"));    ///< Reciever Station
        ui->dataPathLbl->setText(tr("原始数据路径")); ///< Origin Data Path

        ui->textHeaderFrame->show();
        ui->gatherInfoGbx->show();
        /// ======
        adjustSize();
        /// ======
        updateScopeInfo();
    }
}

void ExportSegyDlg::on_shotRbtn_clicked(bool checked)
{
    if(checked)
    {
        ui->ScopeGbx->setTitle(tr("炮范围:"));
        ui->lineLbl->setText(tr("炮线序号:"));
        ui->stationLbl->setText(tr("站点号:"));
        ui->dataPathLbl->setText(tr("接收数据路径:"));

        ui->textHeaderFrame->hide();
        ui->gatherInfoGbx->hide();
        /// ======
        adjustSize();
        /// ======
        updateScopeInfo();
    }
}

void ExportSegyDlg::on_fromLineSpx_valueChanged(int arg1)
{
    if(arg1>ui->toLineSpx->value())
    {
        ui->toLineSpx->setValue(arg1);
    }
}

void ExportSegyDlg::on_toLineSpx_valueChanged(int arg1)
{
    if(arg1<ui->fromLineSpx->value())
    {
        ui->fromLineSpx->setValue(arg1);
    }
}

void ExportSegyDlg::on_fromStaSpx_valueChanged(int arg1)
{
    if(arg1>ui->toStaSpx->value())
    {
        ui->toStaSpx->setValue(arg1);
    }
}

void ExportSegyDlg::on_toStaSpx_valueChanged(int arg1)
{
    if(arg1<ui->fromStaSpx->value())
    {
        ui->fromStaSpx->setValue(arg1);
    }
}

void ExportSegyDlg::on_dataPathBrwser_clicked()
{
    QString dataPath = QFileDialog::getExistingDirectory(this, tr("选择原始数据路径."),QDir::currentPath());
    if(dataPath.isEmpty())
    {
        return;
    }
    ui->dataPathEdit->setText(dataPath);
}

void ExportSegyDlg::on_outputPathBrwser_clicked()
{
    QString dataPath = QFileDialog::getExistingDirectory(this,tr("选择输出数据路径"), QDir::currentPath());
    if(dataPath.isEmpty())
    {
        return;
    }
    ui->outputFilePathEdit->setText(dataPath);
}

void ExportSegyDlg::on_startBtn_clicked()
{
    /// ====== 判断处理数据类型-共检波点/共炮
    if(ui->recvRbtn->isChecked())
    {
        m_exportParameters.segyType = 0;
    }
    else
    {
        m_exportParameters.segyType = 1;
    }
    /// ====== job name
    if(ui->jobEdit->text().isEmpty())
    {
        QMessageBox::warning(this, tr("警告"), tr("请输入Job名."), tr("确定"));
        return;
    }
    m_exportParameters.jobName = ui->jobEdit->text().trimmed();
    //area
    if(ui->areasCbx->currentText().isEmpty())
    {
        QMessageBox::warning(this, tr("警告"), tr("请选择Area."), tr("确定"));
        return;
    }
    m_exportParameters.areaName = ui->areasCbx->currentText();
    /// ====== 数据目录
    if(ui->dataPathEdit->text().isEmpty())
    {
        QMessageBox::warning(this, tr("警告"), tr("请选择输入数据路径."), tr("确定"));
        return;
    }
    if(!QDir(ui->dataPathEdit->text()).exists())
    {
        QMessageBox::warning(this, tr("警告"), tr("输入数据路径不存在"), tr("确定"));
        return;
    }
    m_exportParameters.dataPath = ui->dataPathEdit->text();
    /// ====== 输出数据相关
    if(ui->outputFilePathEdit->text().isEmpty())
    {
        QMessageBox::warning(this, tr("警告"), tr("请选择输出数据路径."), tr("确定"));
        return;
    }
    if(!QDir(ui->outputFilePathEdit->text()).exists())
    {
        QMessageBox::warning(this, tr("警告"), tr("输出数据路径不存在."), tr("确定"));
        return;
    }
    m_exportParameters.outputPath = ui->outputFilePathEdit->text();
    /// ====== 共检波点数据文件信息
    if(m_exportParameters.segyType == 0)
    {
        /// ====== trace len
        const QValidator *validator = ui->traceLenEdit->validator();
        int pos = 0;
        QString text = ui->traceLenEdit->text();
        if(validator->validate(text,pos) != QValidator::Acceptable)
        {
            QMessageBox::warning(this, tr("警告"), tr("道数据长度范围必须为:100~100000."), tr("确定"));
            return;
        }
        m_exportParameters.traceNs = ui->traceLenEdit->text().toInt();
        m_exportParameters.ds      = ui->dsSpx->value();

        /// ====== shotlineFiles
        if(m_shotLineDlg->shotLineFiles().size()<1)
        {
            QMessageBox::warning(this, tr("警告"), tr("需要选择ShotLine文件."), tr("确定"));
            return;
        }
        m_exportParameters.shotLineFiles = m_shotLineDlg->shotLineFiles();

        //text header
        m_exportParameters.textHeader = ui->textEdit->toPlainText();
    }
    //作业范围
    m_exportParameters.lineScope.first  = ui->fromLineSpx->value();
    m_exportParameters.lineScope.second = ui->toLineSpx->value();
    m_exportParameters.staScope.first  = ui->fromStaSpx->value();
    m_exportParameters.staScope.second = ui->toStaSpx->value();
    /// ====== 输出Job文件到工区目录
    QString jobFileName = m_exportParameters.projectPath+"/work/"+m_exportParameters.jobName;
    if(saveJobParameter(jobFileName, m_exportParameters))
    {
        return;
    }
    /// ====== 启动输出SEGY数据进程
    QStringList argList;
    argList << jobFileName;
    QString program;
#ifdef Q_OS_LINUX
    //程序
    program = QApplication::applicationDirPath()+Dir_Separator+"ExportSegyProgram";
#else  //Q_OS_WIN
    program = QApplication::applicationDirPath()+Dir_Separator+"ExportSegyProgram.exe";
#endif
    QProcess process;
    process.startDetached(program,argList);
    this->close();
}

/// ====== 输出Job文件到工区目录
/// 参数说明: jobFile:  Job文件名
///          paramter: Job参数信息
bool ExportSegyDlg::saveJobParameter(const QString &jobFile,const ExportSegyParameter &paramter)
{
    QFile file(jobFile);
    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(this, tr("错误"), tr("打开Job文件错误,请检查工区."), tr("确定"));
        return false;
    }
    //保存成json 格式
    QJsonDocument doc;
    QJsonObject   jsobj;
    //保存参数----
    jsobj.insert(Json_Key_JobName,paramter.jobName);
    jsobj.insert(Json_Key_JobType,paramter.segyType);
    jsobj.insert(Json_Key_ProjectPath,paramter.projectPath);
    jsobj.insert(Json_Key_ProjectName,paramter.projectName);
    jsobj.insert(Json_key_AreaName,paramter.areaName);
    jsobj.insert(Json_key_DataPath,paramter.dataPath);
    jsobj.insert(Json_key_OutputPath,paramter.outputPath);
    jsobj.insert(Json_key_LineScope,QString("%1|%2").arg(paramter.lineScope.first).arg(paramter.lineScope.second));
    jsobj.insert(Json_key_StationScope,QString("%1|%2").arg(paramter.staScope.first).arg(paramter.staScope.second));
    //共检波点数据类型
    if(paramter.segyType == 0)
    {
        jsobj.insert(Json_key_NS,paramter.traceNs);
        jsobj.insert(Json_key_DS,paramter.ds);
        //保存炮线文件，卷头文本
        QJsonArray shotLinesArray;
        foreach (QString shotLine, paramter.shotLineFiles)
        {
            shotLinesArray.append(shotLine);
        }
        jsobj.insert(Json_key_ShotLineFiles,shotLinesArray);
        jsobj.insert(Json_key_SegyTextHeader,paramter.textHeader);
    }
    doc.setObject(jsobj);
    file.write(doc.toJson());
    file.close();
    return true;
}
