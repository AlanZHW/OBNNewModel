#include "createareadialog.h"

CreateAreaDialog::CreateAreaDialog(QWidget *parent)
    :AbstractAreaDialog(parent)
{
    this->setWindowTitle("创建观测系统");
    setOptBtnText("创建观测系统");
    setAreaOption(CreateArea);
}

/// ======
void CreateAreaDialog::run()
{
    //判断工区名是否合法,是否已经存在等
    QString area_name = areaName();
    int index = area_name.indexOf(QRegExp(ILLEGAL_CHARS));
    if(index>=0)
    {
        QMessageBox::warning(this,"warning",QString("Area name contains invalid char \"%1\"").arg(area_name.at(index)));
        return;
    }
    QString areaFile = m_projInfo.ProjectPath + Dir_Separator+area_name;
    qDebug() << "areaFile = " << areaFile;
    /// ======
    QFileInfo info(areaFile);
    //已经存在文件或者目录
    if(info.exists())
    {
        //是文件，直接删除
        if(info.isFile())
        {
            QFile file(info.absoluteFilePath());
            file.remove();
        }
        //目录，提示是否覆盖
        if(info.isDir())
        {
            QMessageBox box(QMessageBox::Warning,tr("warning"),tr("The dir has been existed, do you wan to overwrite it?"),QMessageBox::Yes |QMessageBox::No,this);
            switch(box.exec())
            {
            case QMessageBox::Yes:
            {
                //先删除该工区
                int ok = Area::deleteArea(m_projInfo,area_name);
                if(ok != 0)
                {
                    QMessageBox::warning(this,"warning", QString("Delete Area Failed.ok=%1").arg(ok));
                    return;
                }
            }
                break;
            case QMessageBox::No:
                return;
            }
        }
    }

    /// ====== 开始执行新建观测系统功能
    setProgressInfo(tr("正在读取SPS文件"), 1);
    AreaDataInfo  *areaDataInfo = new AreaDataInfo;
    int ok = 0;
    QString errStr;
    ok = gobs_sps_files_SR_read(spsFiles(), areaDataInfo, &errStr);
    if(ok !=0 )
    {
        QMessageBox::warning(this,"error","Read SPS File Error:"+errStr);
        return;
    }

    setProgressInfo(tr("创建观测系统..."), 20);
    ok = Area::createArea(m_projInfo, area_name, spsFiles());
    if(ok !=0 )
    {
        qDebug()<<"create area ok:"<<ok;
        QMessageBox::warning(this,"error","Create Area Failed.");
        return;
    }
    setProgressInfo(tr("创建观测系统成功"), 100);
}

void CreateAreaDialog::slotHelp()
{
    QMessageBox::information(this,"Help Information","To create a new area," "Input a areaName,and select sps files, and S,R files are" "needed, X file is optional.");
}
