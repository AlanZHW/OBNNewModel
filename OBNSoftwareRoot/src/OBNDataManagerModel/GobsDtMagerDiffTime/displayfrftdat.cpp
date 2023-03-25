#include "displayfrftdat.h"
#include "ui_displayfrftdat.h"

DisplayFrftDat::DisplayFrftDat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisplayFrftDat)
{
    ui->setupUi(this);
    mDataCont = 0;
    mDataInfo = NULL;
    mTimeData = NULL;
}

DisplayFrftDat::~DisplayFrftDat()
{
    if(NULL != mDataInfo)
        delete [] mDataInfo;
    if(NULL != mTimeData)
        delete [] mTimeData;
    delete ui;
}

//====设置frft振幅数据文件,并读取文件中的内容进行显示
void DisplayFrftDat::setFrftOutData(QString frftOneTFName)
{
    //====读取frft振幅数据
    QFile file(frftOneTFName);
    if(!file.exists())//===判断文件是否存在
        return;
    if(!file.open(QIODevice::ReadOnly))//====以只读的当时打开当前文件
        return;

    QList<float> dataTimeList, dataValueList;
    QStringList ReadLineData;
    QTextStream in(&file);
    while(!in.atEnd())
    {
        ReadLineData = in.readLine().split(QRegExp("\\s+"));
        float tmpDataTime = ReadLineData.at(0).toFloat();
        dataTimeList.append(tmpDataTime);

        float tmpDataValue= ReadLineData.at(1).toFloat();
        dataValueList.append(tmpDataValue);
    }
    file.close();

    mDataCont = dataValueList.count();
    mTimeCont = dataTimeList.count();
    if(NULL != mDataInfo)
        delete [] mDataInfo;
    if(NULL != mTimeData)
        delete [] mTimeData;

    mDataInfo = new float[mDataCont];
    mTimeData = new float[mDataCont];
    for(int iList = 0; iList < dataValueList.count(); iList ++)
        mDataInfo[iList] = dataValueList.at(iList);
    for(int iList = 0; iList < dataTimeList.count(); iList ++)
        mTimeData[iList] = dataTimeList.at(iList);
}

QPoint DisplayFrftDat::origin()
{
    QRect r = this->rect();
    return r.center();
}

//====画图部分
void DisplayFrftDat::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    int width  = this->width();
    int height = this->height();

    QRect rect(0,0, width, height);

    painter.drawRect(rect);
    painter.setPen(QPen(QColor(0, 0, 0))); // 设置线条为黑色

    painter.drawLine(QPoint(0, height-10),QPoint(width, height-10)); // x轴
    painter.drawLine(QPoint(10, 0), QPoint(10, height)); // y轴

    if(NULL != mTimeData && NULL != mDataInfo)
    {
        //====获取X方向和Y方向数据值的最大、最小值
        float xScaleMax = mTimeData[0];
        for(int iXScale = 1; iXScale < mTimeCont; iXScale ++)
            xScaleMax = MAX(xScaleMax, mTimeData[iXScale]);
        int   xScaleCont = 0;
        float xTextDisp  = 0;
        if(0 != (int)xScaleMax/1000)
        {
            if(2 <= (int)xScaleMax/1000)
            {
                xScaleCont = (int)xScaleMax/1000+1;
                xTextDisp  = 1000;
            }
            else
            {
                xScaleCont = (int)xScaleMax/100+1;
                xTextDisp  = 100;
            }
        }
        else if(0 != (int)xScaleMax%100)
        {
            if(2 <= (int)xScaleMax%100)
            {
                xScaleCont = (int)xScaleMax/100+1;
                xTextDisp  = 100;
            }
            else
            {
                xScaleCont = (int)xScaleMax/10+1;
                xTextDisp  = 10;
            }
        }
        else if(0 != (int)xScaleMax/10)
        {
            if(2 <= (int)xScaleMax/10)
            {
                xScaleCont = (int)xScaleMax/10+1;
                xTextDisp  = 10;
            }
            else
            {
                xScaleCont = (int)xScaleMax+1;
                xTextDisp  = 1;
            }
        }
        if(10 > (int)xScaleMax)
        {
            if(2 <= (int)xScaleMax)
            {
                xScaleCont = (int)xScaleMax+1;
                xTextDisp  = 1;
            }
            else
            {
                xScaleCont = (int)(xScaleMax/0.1)+1;
                xTextDisp  = 0.1f;
            }
        }

        float yScaleMax = mDataInfo[0];
        for(int iYScale = 1; iYScale < mDataCont; iYScale ++)
            yScaleMax = MAX(yScaleMax, mDataInfo[iYScale]);
        int   yScaleCont= 0;
        float yTextDisp = 0;
        if(0 != (int)yScaleMax/1000)
        {
            if(2 <= (int)yScaleMax/1000)
            {
                yScaleCont = (int)yScaleMax/1000+1;
                yTextDisp  = 1000;
            }
            else
            {
                yScaleCont = (int)yScaleMax/100+1;
                yTextDisp  = 100;
            }
        }
        else if(0 != (int)yScaleMax/100)
        {
            if(2 <= (int)yScaleMax/100)
            {
                yScaleCont = (int)yScaleMax/100+1;
                yTextDisp  = 100;
            }
            else
            {
                yScaleCont = (int)yScaleMax/10+1;
                yTextDisp  = 10;
            }
        }
        else if(0 != (int)yScaleMax/10)
        {
            if(2 <= (int)yScaleMax/10)
            {
                yScaleCont = (int)yScaleMax/10+1;
                yTextDisp  = 10;
            }
            else
            {
                yScaleCont = (int)yScaleMax+1;
                yTextDisp  = 1;
            }
        }
        if((int)yScaleMax < 10)
        {
            if(2 <= (int)yScaleMax)
            {
                yScaleCont = (int)yScaleMax+1;
                yTextDisp  = 1;
            }
            else
            {
                yScaleCont = (int)(yScaleMax/0.1)+1;
                yTextDisp  = 0.1f;
            }
        }
        //====横坐标刻度
        float DispScaleX = (width-10)/xScaleCont;
        for(int ixCont = 1; ixCont < xScaleCont; ixCont ++)
        {
            double scaleXTop = ixCont*DispScaleX+10;
            double scaleYTop = height-20;
            QPoint pScaleTop(scaleXTop, scaleYTop);

            double scaleXBottom = ixCont*DispScaleX+10;
            double scaleYBottom = height-10;
            QPoint pScaleBottom(scaleXBottom, scaleYBottom);

            painter.drawLine(pScaleTop, pScaleBottom);

            QString textInfo = QString::number(ixCont*xTextDisp);
            double scaleXText = ixCont*DispScaleX+10;
            double scaleYText = height;
            QPoint pScaleText(scaleXText, scaleYText);
            painter.drawText(pScaleText, textInfo);
        }
        //====纵坐标刻度
        float DispScaleY = (height-10)/yScaleCont;
        for(int iyCont = 1; iyCont < yScaleCont; iyCont ++)
        {
            double scaleXLeft = 10;
            double scaleYLeft = height-10-iyCont*DispScaleY;
            QPoint pScaleLeft(scaleXLeft, scaleYLeft);

            double scaleXRight = 20;
            double scaleYRight = height-10-iyCont*DispScaleY;
            QPoint pScaleRight(scaleXRight, scaleYRight);

            painter.drawLine(pScaleLeft, pScaleRight);

            QString textInfo = QString::number(iyCont*yTextDisp);
            painter.drawText(pScaleRight, textInfo);
        }
        //====数据曲线图
        double xInfo = -1*mTimeData[0]/xTextDisp*DispScaleX+10;
        double yInfo = -1*mDataInfo[0]/yTextDisp*DispScaleY+10;
        QPoint p1(xInfo, yInfo);
        for(int iNum = 1; iNum < mDataCont; iNum ++)
        {
            double tmpxInfo = mTimeData[iNum]/xTextDisp*DispScaleX+10;
            double tmpyInfo = -1*mDataInfo[iNum]/yTextDisp*DispScaleY+height-10;
            QPoint p2(tmpxInfo, tmpyInfo);
            painter.drawLine(p1, p2);
            p1 = p2;
        }

        //====必要的文字信息
        //====虚线
    }
}
