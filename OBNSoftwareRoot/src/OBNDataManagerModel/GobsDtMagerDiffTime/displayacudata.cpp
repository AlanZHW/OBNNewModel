#include "displayacudata.h"
#include "ui_displayacudata.h"

DisplayAcuData::DisplayAcuData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisplayAcuData)
{
    ui->setupUi(this);
}

DisplayAcuData::~DisplayAcuData()
{
    //====将之前的进行清理
    if(0 != ArrayTimeErr.count())
    {
        for(int iList = 0; iList < ArrayTimeErr.count(); iList ++)
            ArrayTimeErr[iList].clear();
        ArrayTimeErr.clear();
    }
    delete ui;
}

DisplayAcuData::DisplayAcuData(QString pNodeName, QString &pAcuFile, int pHourNum)
{
    new DisplayAcuData(this);

    mNideName = pNodeName;
    mHourNum  = pHourNum;
    //====将之前的进行清理
    if(0 != ArrayTimeErr.count())
    {
        for(int iList = 0; iList < ArrayTimeErr.count(); iList ++)
            ArrayTimeErr[iList].clear();
        ArrayTimeErr.clear();
    }

    //====读取ACU中间文件
    QFile file(pAcuFile);
    if(!file.open(QIODevice::ReadOnly))
        return;
    QTextStream in(&file);
    //====读取时差文件
    QList<QStringList> nReadDtList;
    QString dataLine;
    while(!in.atEnd())
    {
        dataLine = in.readLine().trimmed();
        QStringList nDataList;
        nDataList = dataLine.split(" ");

        nReadDtList.append(nDataList);
    }
    file.close();

    int ColumnNum = nReadDtList.at(0).count();
    for(int iColumn = 0; iColumn < ColumnNum; iColumn ++)
    {
        QList<float> datList;
        int iColumnDtCount = nReadDtList.count();
        for(int idt = 0; idt < iColumnDtCount; idt ++)
        {
            float tmpData = nReadDtList.at(idt).at(iColumn).toFloat();
            datList.append(tmpData);
        }
        ArrayTimeErr.append(datList);
    }
    for(int iList = 0; iList < nReadDtList.count(); iList ++)
    {
        nReadDtList[iList].clear();
    }
    nReadDtList.clear();
}

//====获取ACU中间文件
void DisplayAcuData::setAcuFileName(QString pNodeName, QString &pAcuFile, int pHourNum)
{
    mNideName = pNodeName;
    mHourNum  = pHourNum;

    //====将之前的进行清理
    if(0 != ArrayTimeErr.count())
    {
        for(int iList = 0; iList < ArrayTimeErr.count(); iList ++)
            ArrayTimeErr[iList].clear();
        ArrayTimeErr.clear();
    }

//    FILE *fpOut = fopen("D:\\GOBS\\gobs_data\\hhh.data", "wb");

    //====读取ACU中间文件
    QFile file(pAcuFile);
    if(!file.open(QIODevice::ReadOnly))
        return;
    QTextStream in(&file);
    //====读取时差文件
    QList<QStringList> nReadDtList;
    QStringList dataLine = in.readAll().trimmed().split("\n", QString::SkipEmptyParts);

//    fprintf(fpOut, "file count is:%d\n", dataLine.count());
//    fflush(fpOut);

    for(int iList = 0; iList < dataLine.count(); iList ++)
    {
        if(0 == dataLine.at(iList).compare(QString::fromLocal8Bit("---s---")))
        {
            QStringList tmpDataList;
            nReadDtList.append(tmpDataList);
        }
        else
        {
            QString tmpData = dataLine.at(iList);

            int ListNo = nReadDtList.count() - 1;
            nReadDtList[ListNo].append(tmpData);
        }
    }

    int ColumnNum = nReadDtList.count();
//    fprintf(fpOut, "ColumnNum is:%d\n", ColumnNum);
//    fflush(fpOut);
    for(int iColumn = 0; iColumn < ColumnNum; iColumn ++)
    {
        QList<float> datList;
        int iColumnDtCount = nReadDtList.at(iColumn).count();
        for(int idt = 0; idt < iColumnDtCount; idt ++)
        {
            float tmpData = nReadDtList.at(iColumn).at(idt).toFloat();
            datList.append(tmpData);
        }
        ArrayTimeErr.append(datList);
    }
//    fclose(fpOut);
}

QPoint DisplayAcuData::origin()
{
    QRect r = this->rect();
    return r.center();
}

void DisplayAcuData::paintEvent(QPaintEvent *)
{
//    FILE *fp = fopen("D:\\GOBS\\gobs_data\\data.dt", "wb");

    QPainter painter(this);

    int width = this->width();
    int height = this->height();
    QRect rect(0,0, width, height);

    painter.drawRect(rect);
    painter.setPen(QPen(QColor(0, 0, 0))); // 设置线条为黑色

    QFont fontInfo("Microsoft YaHei", 8, QFont::Thin);
    painter.setFont(fontInfo);

    int base = width/4;
    QPoint o = origin();
    painter.drawLine(QPoint(0, o.y()),QPoint(width, o.y())); // x轴
    painter.drawLine(QPoint(base, 0), QPoint(base, height)); // y轴
//    fprintf(fp, "count = %d\n", ArrayTimeErr.count());
//    fflush(fp);
    if(0 != ArrayTimeErr.count())
    {
        QRectF rect = this->rect();
        painter.drawText(rect, Qt::AlignHCenter, mNideName);

        //====显示必要的文字信息
        QString XAxisInfo  = "X(time/h)";
        QString YAxisInfo  = "Y(Clock error/ms)";
        painter.drawText(QPoint(width-40, height/2+10), XAxisInfo);
        int x = this->width()/4-15;
        painter.rotate(90);
        painter.drawText(0, -x, YAxisInfo);
        painter.rotate(270);

        //====画横纵坐标刻度
        float ymax = ArrayTimeErr.at(0).at(0);
        for(int iList1 = 0; iList1 < ArrayTimeErr.count(); ++ iList1)
        {
            for(int iList2 = 0; iList2 < ArrayTimeErr.at(iList1).count(); ++ iList2)
                ymax = MAX(ymax, ArrayTimeErr.at(iList1).at(iList2));
        }
//        fprintf(fp, "ymax = %f\n", ymax);
//        fflush(fp);

        int     yScaleCont = 0;
        float   yTextDisp  = 0;
        if(0 != (int)ymax/1000)
        {
            if(2 <= (int)ymax/1000)
            {
                yScaleCont = (int)ymax/1000+1;
                yTextDisp  = 1000;
            }
            else
            {
                yScaleCont = (int)ymax/100+1;
                yTextDisp  = 100;
            }
        }
        else if(0 != (int)ymax/100)
        {
            if(2 <= (int)ymax/100)
            {
                yScaleCont = (int)ymax/100+1;
                yTextDisp  = 100;
            }
            else
            {
                yScaleCont = (int)ymax/10+1;
                yTextDisp  = 10;
            }
        }
        else if(0 != (int)ymax/10)
        {
            if(2 <= (int)ymax/10)
            {
                yScaleCont = (int)ymax/10+1;
                yTextDisp  = 10;
            }
            else
            {
                yScaleCont = (int)ymax+1;
                yTextDisp  = 1;
            }
        }
        if(10 > (int)ymax)
        {
            if(2 <= (int)ymax)
            {
                yScaleCont = (int)ymax+1;
                yTextDisp  = 1;
            }
            else
            {
                yScaleCont = (int)(ymax/0.1)+1;
                yTextDisp  = 0.1f;
            }
        }
        int hightDisp   = height/(2*yScaleCont);//====纵坐标轴刻度
        int xScaleCont= ArrayTimeErr.at(0).count()+1;  //====X轴刻度个数
        if(1 < ArrayTimeErr.count())
        {
            for(int iList = 1; iList < ArrayTimeErr.count(); ++ iList)
                xScaleCont = MAX(xScaleCont, ArrayTimeErr.at(iList).count()+1);
        }

        float xwidth    = (width-width/4)/xScaleCont;  //====相邻两个刻度的宽度

        QString OriginScaleInfo = "0/" + QString::number(mHourNum);
        painter.drawText(base, height/2+10, OriginScaleInfo);
        //====X轴之上的
        for(int iScale = 1; iScale <= yScaleCont; iScale ++)
        {
            double scaleXLeft = width/4;
            double scaleYLeft = height/2-iScale*hightDisp;

            double scaleXRight = width/4 + 10;
            double scaleYRight = height/2-iScale*hightDisp;

            QPoint pScaleLeft(scaleXLeft, scaleYLeft);
            QPoint pScaleRight(scaleXRight, scaleYRight);

            painter.drawLine(pScaleLeft, pScaleRight);

            int ScaleValue   = iScale*yTextDisp;
            QString scaleNum = QString::number(ScaleValue);
            painter.drawText(pScaleRight, scaleNum);
        }
        //====X轴之下的
        for(int iScale = 1; iScale <= yScaleCont; iScale ++)
        {
            double scaleXLeft = width/4;
            double scaleYLeft = height/2+iScale*hightDisp;

            double scaleXRight = width/4 + 10;
            double scaleYRight = height/2+iScale*hightDisp;

            QPoint pScaleLeft(scaleXLeft, scaleYLeft);
            QPoint pScaleRight(scaleXRight, scaleYRight);

            painter.drawLine(pScaleLeft, pScaleRight);

            int scaleValue = -1*iScale*yTextDisp;
            QString scaleNum = QString::number(scaleValue);
            painter.drawText(pScaleRight, scaleNum);
        }
        //====横坐标轴刻度
        for(int iScale = 1; iScale < xScaleCont; iScale ++)
        {
            double scaleXTop = width/4 + iScale*xwidth;
            double scaleYTop = height/2 - 10;

            double scaleXbottom = width/4 + iScale*xwidth;
            double scaleYbottom = height/2;

            QPoint pScaleTop(scaleXTop, scaleYTop);
            QPoint pScaleBottom(scaleXbottom, scaleYbottom);

            painter.drawLine(pScaleTop, pScaleBottom);
            if(0 == iScale%6)
            {
                int scaleValue   = mHourNum + iScale;
                QString scaleNum = QString::number(scaleValue);

                double scaleXScale = width/4 + iScale*xwidth-10;
                double scaleYScale = height/2+10;
                QPoint pScaleScale(scaleXScale, scaleYScale);
                painter.drawText(pScaleScale, scaleNum);
            }
        }

        //====画钟差曲线图
        for(int iListOne = 0; iListOne < ArrayTimeErr.count(); iListOne ++)
        {
            if(iListOne == ArrayTimeErr.count()-1)
                painter.setPen(QPen(QColor(255, 0, 0)));
            double xnum = width/4;
            double ynum = -1*ArrayTimeErr.at(iListOne).at(0)/yTextDisp*hightDisp+height/2;
            QPoint p1(xnum, ynum);
            for(int iListTwo = 1; iListTwo < ArrayTimeErr.at(iListOne).count(); iListTwo ++)
            {
                if(ArrayTimeErr.at(iListOne).at(iListTwo) == 0)
                    continue;
                double txnum = iListTwo*xwidth+width/4;
                double tynum = -1*ArrayTimeErr.at(iListOne).at(iListTwo)/yTextDisp*hightDisp+height/2;

                QPoint p2(txnum, tynum);
                painter.drawLine(p1, p2);
                p1 = p2;
            }
        }

        painter.setPen(QPen(QColor(0, 0, 0)));

        //====画虚线标尺
        QPen pen(Qt::black, 1, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);
        painter.setPen(pen);
        for(int iScale = 1; iScale <= yScaleCont; iScale ++)
        {
            double dttelineUpperXLeft = 0;
            double dttelineUpperYLeft = height/2-iScale*hightDisp;
            QPoint pdttelineUpperLeft(dttelineUpperXLeft, dttelineUpperYLeft);

            double dttelineUpperXRight = width;
            double dttelineUpperYRight = height/2-iScale*hightDisp;
            QPoint pdttelineUpperRight(dttelineUpperXRight, dttelineUpperYRight);

            painter.drawLine(pdttelineUpperLeft, pdttelineUpperRight);

            double dttelineLowerXLeft = 0;
            double dttelineLowerYLeft = height/2+iScale*hightDisp;
            QPoint pdttelineLowerLeft(dttelineLowerXLeft, dttelineLowerYLeft);

            double dttelineLowerXRight = width;
            double dttelineLowerYRight = height/2+iScale*hightDisp;
            QPoint pdttelineLowerRight(dttelineLowerXRight, dttelineLowerYRight);
            painter.drawLine(pdttelineLowerLeft, pdttelineLowerRight);
        }
    }
//            fclose(fp);
}
