#include "updateareadialog.h"

//Update Area------------------------------------------
UpdateAreaDialog::UpdateAreaDialog(QWidget *parent)
    :AbstractAreaDialog(parent)
{
    this->setWindowTitle("修改观测系统");
    setOptBtnText("Update");
    setAreaEditReadOnly(true);
    setAreaOption(UpdateArea);
}
void UpdateAreaDialog::updateArea(const QString &areaName)
{
    setAreaName(areaName);
    this->exec();
}

void UpdateAreaDialog::run()
{
//    QStringList spsFiles = spsFiles();
//    int ok = 0; QString errStr;
//    setProgressInfo("Updating Area...",1);
//    ok = Area::updateArea(m_projInfo, m_currentArea, spsFiles, m_UpdateAreaDialog->updateOption());
//    if(ok !=0 )
//    {
//        qDebug()<<"update area ok:"<<ok;
//        QMessageBox::warning(this,"error","Update Area Failed.");
//        return;
//    }
//    //2 读取数据--------------------
//    spsFiles = Area::spsFiles(m_projInfo,m_currentArea);
//    m_UpdateAreaDialog->setProgressInfo("Reading sps files...",20);
//    AreaDataInfo  *areaDataInfo = new AreaDataInfo;
//    ok = gobs_sps_files_SR_read(spsFiles,areaDataInfo,&errStr);
//    if(ok !=0 )
//    {
//        QMessageBox::warning(this,"error","Read SPS File Error:"+errStr);
//        return;
//    }
}

void UpdateAreaDialog::slotHelp()
{
    QMessageBox::information(this,"Help Information","To update the current area with new sps files,"
                                                     ",please select sps files, and S,R files are"
                                                     "needed, X file is optional.");
}
