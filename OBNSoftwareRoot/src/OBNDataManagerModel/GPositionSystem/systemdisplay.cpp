#include "systemdisplay.h"
#include "ui_systemdisplay.h"

systemdisplay::systemdisplay(QWidget *parent) :
    QWidget(parent),flag(false),flagGPS(false),flagAfter(false),
    ui(new Ui::systemdisplay)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_StyledBackground,true);
    this->setStyleSheet("background-color: rgb(255,255, 255)");
    m_SystemCoordVector.clear();
}

systemdisplay::~systemdisplay()
{
    delete ui;
}

void systemdisplay::initWindows()
{
    flag    = false;
    flagGPS = false;
    m_SystemCoordVector.clear();
}

void systemdisplay::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    int height = this->height();
    int width  = this->width();

    int nRectWidth = width-120;
    int nRectHeigth= height-60;
    QRect rect(60, 30, nRectWidth, nRectHeigth);
    painter.drawRect(rect);

    QPoint nPointHo(60, height/2);
    QPoint nPointH1(width-60, height/2);
    painter.drawLine(nPointHo, nPointH1);

    QPoint nPointVo(width/2, 30);
    QPoint nPointV1(width/2, height-30);
    painter.drawLine(nPointVo, nPointV1);

    /// 画其他刻度虚线
    QPen penA(Qt::black, 1, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(penA);

    QPoint nPointH2(60, 30+(height-60)/4);
    QPoint nPointH3(width-60, 30+(height-60)/4);
    painter.drawLine(nPointH2, nPointH3);

    QPoint nPointH4(60,       height/2+(height-60)/4);
    QPoint nPointH5(width-60, height/2+(height-60)/4);
    painter.drawLine(nPointH4, nPointH5);

    QPoint nPointV2(60+(width-120)/4,       30);
    QPoint nPointV3(60+(width-120)/4, height-30);
    painter.drawLine(nPointV2, nPointV3);

    QPoint nPointV4(width/2+(width-120)/4, 30);
    QPoint nPointV5(width/2+(width-120)/4, height-30);
    painter.drawLine(nPointV4, nPointV5);

    if(flag)/// 当获取到原点坐标时,将坐标系刻度添加上去
    {
        painter.drawText(QPoint(0, height/2+5), QString("%1").arg(mY0, 0, 'f', 2));
        double topTextY = mY0+mZ0*5;
        painter.drawText(QPoint(0, 35), QString("%1").arg(topTextY, 0, 'f', 2));
        double bottomTextY = mY0-mZ0*5;
        painter.drawText(QPoint(0, height-25), QString("%1").arg(bottomTextY, 0, 'f', 2));

        painter.drawText(QPoint(width/2-30, height-20), QString("%1").arg(mX0, 0, 'f', 2));
        double leftTextX = mX0-mZ0*5;
        painter.drawText(QPoint(30, height-15), QString("%1").arg(leftTextX, 0, 'f', 2));
        double RightTextX = mX0+mZ0*5;
        painter.drawText(QPoint(width-75, height-20), QString("%1").arg(RightTextX, 0, 'f', 2));

        /// 用虚线描一个方框,方框的长为1.7倍的z0(坐标值)
        QPen pen(Qt::black, 1, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);
        painter.setPen(pen);
        int ZRectX = (int)(3.3*width/10)+30;
        int zRectY = (int)(3.3*height/10)+30;
        int ZRectLenX=(int)((width-120)/5*1.7);
        int ZRectLenY=(int)((height-60)/5*1.7);
        QRect ZRect(ZRectX, zRectY, ZRectLenX, ZRectLenY);
        painter.drawRect(ZRect);
    }
    double minX = mX0-mZ0*5;
    double minY = mY0-mZ0*5;
    double maxX = mX0+mZ0*5;
    double maxY = mY0+mZ0*5;
    if(flagGPS)
    {
        if((m_DispCoord.x > minX && m_DispCoord.x < maxX) && (m_DispCoord.y > minY && m_DispCoord.y < maxY))
        {
            if(m_DispCoord.x < mX0 && m_DispCoord.y > mY0)
            {
                int nCoordDispX = width/2 -(fabs(m_DispCoord.x-mX0)*(width/2-60))/(mZ0*5);
                int nCoordDispY = height/2-(fabs(m_DispCoord.y-mY0)*(height/2-30))/(mZ0*5);
                QPoint nCoordGPS(nCoordDispX, nCoordDispY);

                QPen pen(Qt::green, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
                painter.setPen(pen);
                painter.setBrush(Qt::SolidPattern);

                painter.drawEllipse(nCoordGPS, 3, 3);

                int nCoordDispGPSX = width/2 -(fabs(m_DispCoord.GPSX-mX0)*(width/2-60))/(mZ0*5);
                int nCoordDispGPSY = height/2-(fabs(m_DispCoord.GPSY-mY0)*(height/2-30))/(mZ0*5);
                QPoint nCoord(nCoordDispGPSX, nCoordDispGPSY);

                QPen penRed(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
                painter.setPen(penRed);
                painter.setBrush(Qt::SolidPattern);

                painter.drawEllipse(nCoord, 3, 3);
            }
            if(m_DispCoord.x < mX0 && m_DispCoord.y < mY0)
            {
                QPen pen(Qt::green, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
                painter.setPen(pen);
                painter.setBrush(Qt::SolidPattern);

                int nCoordDispX = width/2 -(fabs(m_DispCoord.x-mX0)*(width/2-60))/(mZ0*5);
                int nCoordDispY = height/2+(fabs(m_DispCoord.y-mY0)*(height/2-30))/(mZ0*5);
                QPoint nCoordGPS(nCoordDispX, nCoordDispY);
                painter.drawEllipse(nCoordGPS, 3, 3);

                QPen penRed(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
                painter.setPen(penRed);
                painter.setBrush(Qt::SolidPattern);

                int nCoordDispGPSX = width/2 -(fabs(m_DispCoord.GPSX-mX0)*(width/2-60))/(mZ0*5);
                int nCoordDispGPSY = height/2+(fabs(m_DispCoord.GPSY-mY0)*(height/2-30))/(mZ0*5);
                QPoint nCoord(nCoordDispGPSX, nCoordDispGPSY);
                painter.drawEllipse(nCoord, 3, 3);
            }
            if(m_DispCoord.x > mX0 && m_DispCoord.y < mY0)
            {
                QPen pen(Qt::green, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
                painter.setPen(pen);
                painter.setBrush(Qt::SolidPattern);

                int nCoordDispX = width/2 +(fabs(m_DispCoord.x-mX0)*(width/2-60))/(mZ0*5);
                int nCoordDispY = height/2+(fabs(m_DispCoord.y-mY0)*(height/2-30))/(mZ0*5);
                QPoint nCoordGPS(nCoordDispX, nCoordDispY);
                painter.drawEllipse(nCoordGPS, 3, 3);

                QPen penRed(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
                painter.setPen(penRed);
                painter.setBrush(Qt::SolidPattern);

                int nCoordDispGPSX = width/2 +(fabs(m_DispCoord.GPSX-mX0)*(width/2-60))/(mZ0*5);
                int nCoordDispGPSY = height/2+(fabs(m_DispCoord.GPSY-mY0)*(height/2-30))/(mZ0*5);
                QPoint nCoord(nCoordDispGPSX, nCoordDispGPSY);
                painter.drawEllipse(nCoord, 3, 3);
            }
            if(m_DispCoord.x > mX0 && m_DispCoord.y > mY0)
            {
                QPen pen(Qt::green, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
                painter.setPen(pen);
                painter.setBrush(Qt::SolidPattern);

                int nCoordDispX = width/2 +(fabs(m_DispCoord.x-mX0)*(width/2-60))/(mZ0*5);
                int nCoordDispY = height/2-(fabs(m_DispCoord.y-mY0)*(height/2-30))/(mZ0*5);
                QPoint nCoordGPS(nCoordDispX, nCoordDispY);
                painter.drawEllipse(nCoordGPS, 3, 3);

                QPen penRed(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
                painter.setPen(penRed);
                painter.setBrush(Qt::SolidPattern);

                int nCoordDispGPSX = width/2 +(fabs(m_DispCoord.GPSX-mX0)*(width/2-60))/(mZ0*5);
                int nCoordDispGPSY = height/2-(fabs(m_DispCoord.GPSY-mY0)*(height/2-30))/(mZ0*5);
                QPoint nCoord(nCoordDispGPSX, nCoordDispGPSY);
                painter.drawEllipse(nCoord, 3, 3);
            }
        }
        QPen pen(Qt::green, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        painter.setPen(pen);
        painter.setBrush(Qt::SolidPattern);
    }

    /// 20210815 add
    if(flagAfter)
    {
        QPen penDisp(Qt::yellow, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        painter.setPen(penDisp);
        painter.setBrush(Qt::SolidPattern);

        int nXAlter = width/2 -(fabs(mXAfter-mX0)*(width/2-60))/(mZ0*5);
        int nYAlter = height/2-(fabs(mYAfter-mY0)*(height/2-30))/(mZ0*5);
        QPoint nCoordAlter(nXAlter, nYAlter);

        painter.drawEllipse(nCoordAlter, 3, 3);

        QPen pen199(Qt::green, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        painter.setPen(pen199);
        painter.setBrush(Qt::SolidPattern);
    }

    if(0 != m_SystemCoordVector.count())
    {
        double nOriginX = width/2;
        double nOriginY = height/2;
        QPoint nOriginCoord(nOriginX, nOriginY);

        for(int iList = 0; iList < m_SystemCoordVector.count(); ++ iList)
        {
            if((m_SystemCoordVector[iList].x > minX && m_SystemCoordVector[iList].x < maxX) &&
               (m_SystemCoordVector[iList].y > minY && m_SystemCoordVector[iList].y < maxY))
            {
                if(m_SystemCoordVector[iList].x < mX0 && m_SystemCoordVector[iList].y > mY0)
                {
                    QPen pen(Qt::red, 2, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);
                    painter.setPen(pen);

                    int nCoordSystemX = width/2 -(fabs(m_SystemCoordVector[iList].x-mX0)*(width/2-60))/(mZ0*5);
                    int nCoordSystemY = height/2-(fabs(m_SystemCoordVector[iList].y-mY0)*(height/2-30))/(mZ0*5);
                    QPoint nCoordGPS(nCoordSystemX, nCoordSystemY);
                    painter.drawPoint(nCoordGPS);
                    painter.drawLine(nOriginCoord, nCoordGPS);

                    QPen penZ(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
                    painter.setPen(penZ);

                    QRect nRect(nCoordSystemX, nCoordSystemY, 5, 5);
                    painter.drawRect(nRect);
                }
                if(m_SystemCoordVector[iList].x < mX0 && m_SystemCoordVector[iList].y < mY0)
                {
                    QPen pen(Qt::red, 2, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);
                    painter.setPen(pen);

                    int nCoordSystemX = width/2 -(fabs(m_SystemCoordVector[iList].x-mX0)*(width/2-60))/(mZ0*5);
                    int nCoordSystemY = height/2+(fabs(m_SystemCoordVector[iList].y-mY0)*(height/2-30))/(mZ0*5);
                    QPoint nCoordGPS(nCoordSystemX, nCoordSystemY);
                    painter.drawPoint(nCoordGPS);
                    painter.drawLine(nOriginCoord, nCoordGPS);

                    QPen penZ(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
                    painter.setPen(penZ);
                    QRect nRect(nCoordSystemX, nCoordSystemY, 5, 5);
                    painter.drawRect(nRect);
                }
                if(m_SystemCoordVector[iList].x > mX0 && m_SystemCoordVector[iList].y < mY0)
                {
                    QPen pen(Qt::red, 2, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);
                    painter.setPen(pen);

                    int nCoordSystemX = width/2 +(fabs(m_SystemCoordVector[iList].x-mX0)*(width/2-60))/(mZ0*5);
                    int nCoordSystemY = height/2+(fabs(m_SystemCoordVector[iList].y-mY0)*(height/2-30))/(mZ0*5);
                    QPoint nCoordGPS(nCoordSystemX, nCoordSystemY);
                    painter.drawPoint(nCoordGPS);
                    painter.drawLine(nOriginCoord, nCoordGPS);

                    QPen penZ(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
                    painter.setPen(penZ);
                    QRect nRect(nCoordSystemX, nCoordSystemY, 5, 5);
                    painter.drawRect(nRect);
                }
                if(m_SystemCoordVector[iList].x > mX0 && m_SystemCoordVector[iList].y > mY0)
                {
                    QPen pen(Qt::red, 2, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);
                    painter.setPen(pen);

                    int nCoordSystemX = width/2 +(fabs(m_SystemCoordVector[iList].x-mX0)*(width/2-60))/(mZ0*5);
                    int nCoordSystemY = height/2-(fabs(m_SystemCoordVector[iList].y-mY0)*(height/2-30))/(mZ0*5);
                    QPoint nCoordGPS(nCoordSystemX, nCoordSystemY);
                    painter.drawPoint(nCoordGPS);
                    painter.drawLine(nOriginCoord, nCoordGPS);

                    QPen penZ(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
                    painter.setPen(penZ);
                    QRect nRect(nCoordSystemX, nCoordSystemY, 5, 5);
                    painter.drawRect(nRect);
                }
            }
        }
    }
    if(0 != m_SystemCoordGOBSVec.count())
    {
        QPen nPen(Qt::red, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        painter.setPen(nPen);
        for(int iList = 0; iList < m_SystemCoordGOBSVec.count(); iList ++)
        {
            if((m_SystemCoordGOBSVec[iList].x > minX && m_SystemCoordGOBSVec[iList].x < maxX) &&
               (m_SystemCoordGOBSVec[iList].y > minY && m_SystemCoordGOBSVec[iList].y < maxY))
            {
                if(m_SystemCoordGOBSVec[iList].x < mX0 && m_SystemCoordGOBSVec[iList].y > mY0)
                {
                    int nCoordSystemX = width/2 -(fabs(m_SystemCoordGOBSVec[iList].x-mX0)*(width/2-60))/(mZ0*5);
                    int nCoordSystemY = height/2-(fabs(m_SystemCoordGOBSVec[iList].y-mY0)*(height/2-30))/(mZ0*5);

                    QRect nRect(nCoordSystemX, nCoordSystemY, 6, 6);
                    painter.drawEllipse(nRect);
//                    painter.drawText(nCoordSystemX, nCoordSystemY, QString::number(m_SystemCoordGOBSVec[iList].h));
                }
                if(m_SystemCoordGOBSVec[iList].x < mX0 && m_SystemCoordGOBSVec[iList].y < mY0)
                {
                    int nCoordSystemX = width/2 -(fabs(m_SystemCoordGOBSVec[iList].x-mX0)*(width/2-60))/(mZ0*5);
                    int nCoordSystemY = height/2+(fabs(m_SystemCoordGOBSVec[iList].y-mY0)*(height/2-30))/(mZ0*5);

                    QRect nRect(nCoordSystemX, nCoordSystemY, 6, 6);
                    painter.drawEllipse(nRect);
//                    painter.drawText(nCoordSystemX, nCoordSystemY, QString::number(m_SystemCoordGOBSVec[iList].h));
                }
                if(m_SystemCoordGOBSVec[iList].x > mX0 && m_SystemCoordGOBSVec[iList].y < mY0)
                {
                    int nCoordSystemX = width/2 +(fabs(m_SystemCoordGOBSVec[iList].x-mX0)*(width/2-60))/(mZ0*5);
                    int nCoordSystemY = height/2+(fabs(m_SystemCoordGOBSVec[iList].y-mY0)*(height/2-30))/(mZ0*5);

                    QRect nRect(nCoordSystemX, nCoordSystemY, 6, 6);
                    painter.drawEllipse(nRect);
//                    painter.drawText(nCoordSystemX, nCoordSystemY, QString::number(m_SystemCoordGOBSVec[iList].h));
                }
                if(m_SystemCoordGOBSVec[iList].x > mX0 && m_SystemCoordGOBSVec[iList].y > mY0)
                {
                    int nCoordSystemX = width/2 +(fabs(m_SystemCoordGOBSVec[iList].x-mX0)*(width/2-60))/(mZ0*5);
                    int nCoordSystemY = height/2-(fabs(m_SystemCoordGOBSVec[iList].y-mY0)*(height/2-30))/(mZ0*5);

                    QRect nRect(nCoordSystemX, nCoordSystemY, 6, 6);
                    painter.drawEllipse(nRect);
//                    painter.drawText(nCoordSystemX, nCoordSystemY, QString::number(m_SystemCoordGOBSVec[iList].h));
                }
            }
        }
    }
}

void systemdisplay::dispCoordCurrent(const double pX, const double pY, const double pGPSX, const double pGPSY)
{

    m_DispCoord.x = pX;
    m_DispCoord.y = pY;
    m_DispCoord.GPSX = pGPSX;
    m_DispCoord.GPSY = pGPSY;

    flagGPS = true;
    this->update();
}

/// 接收坐标系原点坐标,并对界面进行绘制
void systemdisplay::setCoordSystemInfo(const double& pX0, const double& pY0, const double& pZ0)
{
    flag= true;
    mX0 = pX0;
    mY0 = pY0;
    mZ0 = pZ0;
    this->update();
}

void systemdisplay::setCoordAfterCalculator(const double& pX, const double& pY, const double& pZ)
{
    flagAfter = true;
    mXAfter = pX;
    mYAfter = pY;
    mZAfter = pZ;
    this->update();
}

/// 获取GPS坐标,并执行画图操作
void systemdisplay::setCoordforGPS(const double& pX, const double& pY)
{
    SystemCoord nGPSCoord;
    nGPSCoord.x = pX;
    nGPSCoord.y = pY;
    m_SystemCoordVector.append(nGPSCoord);
    this->update();
}

void systemdisplay::setGOBSCoord(const double& pX, const double& pY, const double& pZ)
{
    SystemCoordGOBS nGOBSCoord;
    nGOBSCoord.x = pX;
    nGOBSCoord.y = pY;
    nGOBSCoord.h = pZ;
    m_SystemCoordGOBSVec.append(nGOBSCoord);
    this->update();
}
