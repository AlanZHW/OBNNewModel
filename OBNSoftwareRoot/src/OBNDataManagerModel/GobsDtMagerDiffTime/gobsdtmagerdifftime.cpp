#include "gobsdtmagerdifftime.h"
#include "ui_gobsdtmagerdifftime.h"

GobsDtMagerDiffTime::GobsDtMagerDiffTime(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GobsDtMagerDiffTime)
{
    ui->setupUi(this);
    m_Row   = -1;
    m_Column= -1;
    setWindowTitle(tr("水声信号分析"));
    //====处理ACU文件线程设置
    tmpVistAcuFile = new VisitACUFile;
    connect(tmpVistAcuFile, SIGNAL(signalSuccess(QStringList)), this, SLOT(slotReadACUSuccess(QStringList)));
    //====设置表格信息
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->verticalHeader()->setStretchLastSection(true);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //====设置界面参数
    ui->lineEditN1->setText("43008");
    ui->lineEditFs->setText("46544");
    ui->lineEditDistance->setText("150");
    ui->lineEditB->setText("4000");
    ui->lineEditF0->setText("12000");
}

GobsDtMagerDiffTime::~GobsDtMagerDiffTime()
{
    delete ui;
}

//====获取输出数据路径
void GobsDtMagerDiffTime::on_PushBrowse_clicked()
{
    m_InputfPath = QFileDialog::getExistingDirectory(this, "Select Origin Data Path", "./");
    if(m_InputfPath.isEmpty())
        return;
    ui->lineEditOriginPath->setText(m_InputfPath);
}

void GobsDtMagerDiffTime::setProjInfo(ProjectInfo* p_projInfo)
{
    mProjectInfo = p_projInfo;
    QString projFile = mProjectInfo->ProjectPath+Dir_Separator+mProjectInfo->ProjectName+Project_File_Suffix;
    QStringList areaList = Area::areasFromProject(projFile);
    ui->comboBox->addItems(areaList);
}

//void GobsDtMagerDiffTime::setProjInfo(const QString& pProjPath, const QString& pProjName)
//{
//    QString projFile = pProjPath+Dir_Separator+pProjName+Project_File_Suffix;
//    QStringList areaList = Area::areasFromProject(projFile);
//    ui->comboBox->addItems(areaList);
//}

//====获取路径下所有设备的名字, 并显示在界面上
void GobsDtMagerDiffTime::setInputfPath(const QString &inoutfPath)
{
    m_InputfPath = inoutfPath;
    QDir dir(inoutfPath);
    QStringList subDirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    //去除非"G"(或者“192”)开头的文件
    for(int i=subDirs.size()-1; i>=0; i--)
    {
        if(!subDirs.at(i).startsWith("G")&&!subDirs.at(i).startsWith("192"))
            subDirs.removeAt(i);
    }
    if(subDirs.size() <= 0)
    {
        m_errString = "Data Path Contains No Data File";
        return ;
    }
    //====设置界面信息
    int rowCount = subDirs.size();
    ui->tableWidget->setRowCount(100);
    ui->tableWidget->setColumnCount(2);
    for(int iRow = 0; iRow < rowCount; iRow ++)
        ui->tableWidget->setItem(iRow, 0, new QTableWidgetItem(subDirs.at(iRow)));
}

//====点击界面生效按钮后,开始计算相关信息,并显示在界面上
void GobsDtMagerDiffTime::on_PushImplement_clicked()
{
    FILE* fp = fopen("./11.dat", "w+");
//    fclose(fp);

    //====判读当前界面的输入信息是否正确和已经被填写
    if(m_InputfPath.isEmpty())//====判断文件路径是否已经选择
    {
        QMessageBox::warning(this, "Error", "Input file dir is NULL, pls check it.");
        return;
    }
    //====判断界面参数是否完整
    if(ui->lineEditN1->text().isEmpty())
    {
        QMessageBox::warning(this, "Error", "One sample count edit is NULL, pls check it.");
        return;
    }
    if(ui->EditConfig->text().isEmpty())
    {
        QMessageBox::warning(this, "Error", "Please select config file.");
        return ;
    }
    QString ConfigName = ui->EditConfig->text();
    fprintf(fp,"conde \n");


    fprintf(fp,"ConfigName = %s\n",ConfigName.toStdString().c_str());
    fflush(fp);

    int N1    = ui->lineEditN1->text().toInt();//N1为每小时一次的采样点数
    double fs = ui->lineEditFs->text().toDouble();//采样率
    int fsdev =   100;
    int timedef = 100;
    double distance = ui->lineEditDistance->text().toDouble();
    double B        = ui->lineEditB->text().toDouble();
    int f0          = ui->lineEditF0->text().toInt();  //中心频率
    QString nAreaName = ui->comboBox->currentText();
    double distanceValue = -1;
    if(0 != distance)
    {
        distanceValue = distance;
    }
    else
    {
        distanceValue = 0;
    }

    //====获取当前路径下所有的有效的ACU文件==解析ACU文件列表
    QDir dir(m_InputfPath);
    QStringList subDirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    //去除非"G"(或者“192”)开头的文件

    fprintf(fp,"m_InputfPath = %s\n",m_InputfPath.toStdString().c_str());
    fflush(fp);
    int dirCont = subDirs.size();

    for(int i=subDirs.size()-1; i>=0; i--)
    {
        if(!subDirs.at(i).startsWith("G")&&!subDirs.at(i).startsWith("192"))
            subDirs.removeAt(i);
    }

    fprintf(fp,"dirCont = %d\n",dirCont);
    fflush(fp);

    if(subDirs.size() <= 0)
    {
        m_errString = "Data Path Contains No Data File";
        return ;
    }

    //====设置界面信息
    AcufInfoList.clear();

    for(int idir = 0; idir < dirCont; idir ++)
    {
        QString DirfromDataList = m_InputfPath + "//" + subDirs.at(idir);   //====DataList文件路径
        QString FileNamefromData= DirfromDataList + "//" + "DataFile.lst";  //====DataList文件名(全路径)
        //====读取DataList文件，获取ACU文件名
        fprintf(fp,"DirfromDataList = %s\n",FileNamefromData.toStdString().c_str());
        fflush(fp);
        QFile file(FileNamefromData);
        if(!file.exists())
        {
            QMessageBox::warning(this, "warning", "Not found DataFile.lst file");
            return;
        }
        if(!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::warning(this, "warning", "Open DataFile.lst failed.");
            return;
        }
        QTextStream in(&file);
        QStringList fileList = in.readAll().split("\n",QString::SkipEmptyParts);

//        fprintf(fp,"fileList = %s\n",fileList.toStdList());
        fflush(fp);

        //====查找最后一个AcuData 0001
//        int idxAcu0 = fileList.lastIndexOf(QRegularExpression("AcuData 0001 .*"));//===最初的版本,10月更改
        int idxAcu0 = fileList.lastIndexOf(QRegularExpression("0001 .*"));
        fprintf(fp,"idxAcu0 = %d\n",idxAcu0);
        fflush(fp);
        if(idxAcu0 < 0)
        {
            QMessageBox::warning(this, "warning", "Not found acu file.");

            file.close();
            return;
        }
        QStringList acuStrList = fileList[idxAcu0].split(QRegExp("\\s+"));
		QStringList acuFileList = fileList[idxAcu0+1].split(QRegExp("\\s+"));



        AcufileInfo AcuFInfo;
        AcuFInfo.NodeName         = subDirs.at(idir);
		AcuFInfo.AcufileName = DirfromDataList + "//" + acuFileList.at(3);                  //====保存ACU文件名
		AcuFInfo.AcufileStartTime = QString("%1 %2").arg(acuFileList[1], acuFileList[2].left(12));//====保存ACU文件起始时间
        AcufInfoList.append(AcuFInfo);//====将ACU文件信息放到链表中

        fprintf(fp,"acuFileList = %s\n",AcuFInfo.AcufileName.toStdString().c_str());
        fflush(fp);

        file.close();//====关闭打开的文件(DataList)
    }
    TotalAcufileCont = AcufInfoList.count();//====保存ACU文件总数
//FILE *fp = fopen("D:\\GOBS\\gobs_data\\000.dat", "wb");
//fclose(fp);
    qDebug() << "read acu file";
    fprintf(fp,"read acu file final");
    fclose(fp);
    //====调用线程处理ACU文件信息
    tmpVistAcuFile->setAcufileInfo(AcufInfoList);
    tmpVistAcuFile->setProjInfo(mProjectInfo);
    tmpVistAcuFile->setAreaName(nAreaName);
    tmpVistAcuFile->setProgremInfo(N1, fs, fsdev, distanceValue, B, f0, timedef);
    tmpVistAcuFile->setConfigfile(ConfigName);
    tmpVistAcuFile->start();
}


//====当所有的ACU文件均处理完成时,开始执行画图程序
void GobsDtMagerDiffTime::slotReadACUSuccess(QStringList pOutfNameList)
{
//   FILE *fp = fopen("D:\\GOBS\\gobs_data\\dddd.data","wb");
//   fprintf(fp, "%d\n", pOutfNameList.count());
//   fflush(fp);
    if(0 == pOutfNameList.count())
        return;

    int RowCount = 0;
    int RowContSum=0;
    RowCount    = pOutfNameList.count()/2;
    RowContSum  = pOutfNameList.count()%2;
    if(0 != RowContSum)
        RowCount += 1;
//    fprintf(fp, "RowCount = %d \t RowContSum = %d\n", RowCount, RowContSum);
//    fclose(fp);
    //====显示图像
    ui->tableWidget->setRowCount(RowCount);
    ui->tableWidget->setColumnCount(4);
    for(int iRow = 0; iRow < RowCount; iRow ++)
    {
        ui->tableWidget->setItem(iRow, 0, new QTableWidgetItem(""));
        ui->tableWidget->setItem(iRow, 1, new QTableWidgetItem(""));
        ui->tableWidget->setItem(iRow, 2, new QTableWidgetItem(""));
        ui->tableWidget->setItem(iRow, 3, new QTableWidgetItem(""));
    }
    for(int iRow = 0; iRow < RowCount; iRow += 2)
    {
        if(iRow == RowCount-1 && 0 != RowContSum)
        {
            QString AcufNameMid     = pOutfNameList.at(iRow)+".TimeErr";
            QStringList timeList = AcufInfoList.at(iRow).AcufileStartTime.split(QRegExp("\\s+"));
            int     HourNum      = timeList.at(1).mid(0, 2).toInt();

            DisplayAcuData *tmpDispAcuDt = new DisplayAcuData();
            tmpDispAcuDt->setAcuFileName(AcufInfoList.at(iRow).NodeName, AcufNameMid, HourNum);
            ui->tableWidget->setCellWidget(iRow, 0, tmpDispAcuDt);

            DisplayFrftDat *tmpDispFrft = new DisplayFrftDat;
            QString tmpFrftDatafName = pOutfNameList.at(iRow)+".TimeAmp";
            tmpDispFrft->setFrftOutData(tmpFrftDatafName);
            ui->tableWidget->setCellWidget(iRow, 1, tmpDispFrft);
        }
        else
        {
            QString AcufNameMid     = pOutfNameList.at(iRow)+".TimeErr";
            QStringList timeList = AcufInfoList.at(iRow).AcufileStartTime.split(QRegExp("\\s+"));
            int     HourNum      = timeList.at(1).mid(0, 2).toInt();

            DisplayAcuData *tmpDispAcuDt = new DisplayAcuData;
            tmpDispAcuDt->setAcuFileName(AcufInfoList.at(iRow).NodeName, AcufNameMid, HourNum);
            ui->tableWidget->setCellWidget(iRow, 0, tmpDispAcuDt);

            DisplayFrftDat *tmpDispFrft = new DisplayFrftDat;
            QString tmpFrftDatafName = pOutfNameList.at(iRow)+".TimeAmp";
            tmpDispFrft->setFrftOutData(tmpFrftDatafName);
            ui->tableWidget->setCellWidget(iRow, 1, tmpDispFrft);

            //=====
            QString AcufNameMidRight  = pOutfNameList.at(iRow+1)+".TimeErr";
            QStringList timeListRight = AcufInfoList.at(iRow+1).AcufileStartTime.split(QRegExp("\\s+"));
            int     HourNumRight      = timeListRight.at(1).mid(0, 2).toInt();

            DisplayAcuData *tmpDispAcuDtRight = new DisplayAcuData;
            tmpDispAcuDtRight->setAcuFileName(AcufInfoList.at(iRow+1).NodeName, AcufNameMidRight, HourNumRight);
            ui->tableWidget->setCellWidget(iRow, 2, tmpDispAcuDtRight);

            DisplayFrftDat *tmpDispFrftRight = new DisplayFrftDat;
            QString tmpFrftDatafNameRight = pOutfNameList.at(iRow+1)+".TimeAmp";
            tmpDispFrftRight->setFrftOutData(tmpFrftDatafNameRight);
            ui->tableWidget->setCellWidget(iRow, 3, tmpDispFrftRight);
        }
    }
    pOutfNameList.clear();
    QMessageBox::information(this, "CUE", "Success.");
}


#if 0
//====单击界面表格事件
void GobsDtMagerDiffTime::slot_tablewidget_cellActivated(int row, int cloumn)
{
}
#endif


void GobsDtMagerDiffTime::on_buttonConfig_clicked()
{
    QString filenameConfig = QFileDialog::getOpenFileName(this, "Open config file", "./");
    if(!filenameConfig.isEmpty())
    {
        ui->EditConfig->setText(filenameConfig);
    }
}
