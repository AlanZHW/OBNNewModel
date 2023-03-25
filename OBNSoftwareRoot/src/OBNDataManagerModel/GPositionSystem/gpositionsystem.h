#ifndef GPOSITIONSYSTEM_H
#define GPOSITIONSYSTEM_H

#include <QLabel>
#include <QFile>
#include <QLineEdit>
#include <QWidget>
#include <QTextEdit>
#include <QTableWidget>
#include <QFileDialog>
#include <QHeaderView>

#include "gpositionsystem_global.h"
#include "gpspublic.h"
#include "systemdisplay.h"
#include "math.h"
//#include "lapacke.h"

#ifdef Q_OS_LINUX
    #include <algorithm>
#else
    #include <windows.h>
#endif

#define MINI(a,b) (a<b)?a:b
#define MAXI(a,b) (a>b)?a:b

namespace Ui {
class GPositionSystem;
}

class GSerialPort;
class QPushButton;
class DeckUnit;
class QTextBrowser;
class PositionChart;
class  GPOSTIONSYTEMSHARED_EXPORT GPositionSystem : public QDialog
{
    Q_OBJECT
public:
    explicit GPositionSystem(QWidget *parent = 0);
    ~GPositionSystem();
    void Postion_AB(QVector<QVector<float> > V_speed, double **pointxyt, double h_high,double h_low,double *x,double *y,double *h);
    double MinDepth(double t,QVector<QVector<float> > V_speed);
    double Postion_R(double h,double t,QVector<QVector<float> > V_speed);
    void   PostionAngle(double t,QVector<QVector<float> > V_speed,double number_goal,double angle_h,double angle_l );
    void testPostion_AB(double **pointxyt, double *x, double *y, double *h);
    void Solve4postion_AB(double **pointxyt, double *x, double *y, double *h);

//    void calculatCoord(int pNO, double** n_pointXYZT, QVector<GPSInfo>& pAGPSInfo, QVector<GPSInfo>& pBGPSInfo, QVector<GPSInfo>& pCGPSInfo,
//                       QVector<GpsCoord>& pGPSCoordVector, QVector<GobsCoord>& pGobsCoordVector);

    void calculat3Coord(int pNO, double** n_pointXYZT,
                                        QVector<GPSInfo>& pAGPSInfo,
                                        QVector<GPSInfo>& pBGPSInfo,
                                        QVector<GPSInfo>& pCGPSInfo,
                                        QVector<GpsCoord>& pGPSCoordVector,
                                        QVector<GobsCoord>& pGobsCoordVector);
    void calculat4Coord(int pNO, double** n_pointXYZT,
                                        QVector<GPSInfo>& pAGPSInfo,
                                        QVector<GPSInfo>& pBGPSInfo,
                                        QVector<GPSInfo>& pCGPSInfo,
                                        QVector<GPSInfo>& pDGPSInfo,
                                        QVector<GpsCoord>& pGPSCoordVector,
                                        QVector<GobsCoord>& pGobsCoordVector);

    void getOptimalValue(QVector<QVector<GobsCoord> >& pGOBSCoordList, double& pX, double& pY, double& pH);
    void MedianFilter(QVector<QVector<GobsCoord> >& data, double& pX, double& pY, double& pZ);
//    void sortGOBSCoordX(GobsCoord* pGOBSCoords, int left, int right);
//    void sortGOBSCoordY(GobsCoord* pGOBSCoords, int left, int right);

    QString            mOBSInfo;
    QVector<GpsCoord>  mGpsCords;
    QVector<GobsCoord> mGobsCords;
    QVector<int>       mDelaytimes;
    QVector<float>     mRange;
    GpsCoord           mGPSCoord;//具体使用的坐标
    QVector<GpsCoord>  mGPSCoordVector;

    /// 保存四个象限坐标信息
    QVector<GPSInfo> mGPSCoordVectorLeftUp;    ///< GPS坐标左上
    QVector<GPSInfo> mGPSCoordVectorRightUp;   ///< GPS坐标右上
    QVector<GPSInfo> mGPSCoordVectorLeftDown;  ///< GPS坐标左下
    QVector<GPSInfo> mGPSCoordVectorRightDown; ///< GPS坐标右下


    QVector<QVector<GpsCoord> >  m_GPSCoordList;    ///<三个象限解算结果数据
    QVector<QVector<GobsCoord> > m_GOBSCoordList;   ///<三个象限解算结果数据
    QVector<QVector<GpsCoord> >  m_GPSCoordList4;   ///<四个象限解算结果数据
    QVector<QVector<GobsCoord> > m_GOBSCoordList4;  ///<四个象限解算结果数据

    QVector<QVector<float>> soundspeed;
protected slots:
    void startPostion();
    void stopPostion();

    //接收到GPS 甲板定位
    void slotRecvGpsCord(const GpsCoord& cord);
    void slotRecvDelaytime(const int&, const double&, const double&, const double&);
    void slotRecvSondaryrange(const float&, const double&, const double&, const double&);
    ///
    void slotRecvSendSignal();
    void slotRecvClickedStart();
    ///
    void slotBrowseVelocity(bool);
    void slot_recv_coordsystem(const double& pX0, const double& pY0, const double& pZ0);
    void slot_recv_coordAfterCalculator(const double&, const double&, const double&);
    void slot_OBS_info(const QString& pOBSMin, const QString& pOBSMax);
    void slot_stop_deckUnit();
public slots:
    void showText(const QString& text);
    void slot_recv_loadinfo(QString loadinfo);

private:
    void createWg();

    void testData();

    Ui::GPositionSystem *ui;
    GSerialPort   *m_gSerialPort;

    DeckUnit        *m_deckUnit;
    PositionChart* m_positionChart;
    systemdisplay* m_systemDis;
    QTextEdit *m_TextEditGPS, *m_TextEditDuck;
    QTableWidget* m_TableGPSInfo;

    //=============================
    QPushButton  *m_startBtn,*m_stopBtn;
    QTextBrowser *m_textBrowser;

    QLineEdit* lineEditVelocityFile;
    QLabel* labelGPSX, *labelGPSY;
    QString m_velocityFName;

    ///
    double h_low, h_high;
    double angle_low, angle_high;
    double* angle;
    int flag;
    int irecindex;
    int sondaryflag;
};

#endif // GPOSITIONSYSTEM_H
