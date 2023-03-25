#include "obncalibrationdatadisplay.h"
#include "ui_obncalibrationdatadisplay.h"

OBNCalibrationDataDisplay::OBNCalibrationDataDisplay(QWidget *parent)
    : QDialog(parent) , m_chartXDisplay(NULL), m_chartYDisplay(NULL), m_chartZDisplay(NULL)
    , ui(new Ui::OBNCalibrationDataDisplay)
{
    ui->setupUi(this);
    /// ====== 设置软件默认最大化显示
    setWindowState(Qt::WindowMaximized);
    setWindowTitle(tr("显示标定数据"));

    //fs=100,fc=10hz,5阶,butterworth-IIR型低通滤波器
    myfilter.len = 6;
    myfilter.a << 1 << -2.75244113481752 << 3.33871807933893 << -2.13725305171939 << 0.713552009831375 << -0.0984430331073669;
    myfilter.b << 0.00200415217268850 << 0.0100207608634425 << 0.0200415217268850 << 0.0200415217268850 << 0.0100207608634425 << 0.00200415217268850;

    connect(ui->pushButtonBrowse, &QPushButton::clicked, this, [=](bool){
        QString inputDir = QFileDialog::getExistingDirectory(this, tr("选择数据所在目录"), "/home/datuo/ZHW/Tool/OBNSoftwareRoot/data/ADJ", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        if(inputDir.isEmpty())
        {
            return;
        }
        ui->lineEdit->setText(inputDir);

        /// ====== 获取当前路径下所有ADJ文件
        QDir adjPathDir(inputDir);
        QStringList adjFileNameList = adjPathDir.entryList(QDir::NoDotAndDotDot|QDir::Files, QDir::Name);
        for(int iList = 0; iList < adjFileNameList.count(); iList ++)
        {
            if(-1 != adjFileNameList[iList].indexOf(".ADJ"))
            {
                QString nRealfileName = inputDir + "/" + adjFileNameList[iList];
                m_adjFileNameList.append(nRealfileName);
            }
        }
        qDebug() << "获取当前路径下所有ADJ文件";
        /// ====== 读取ADJ文件内容
        readADJFileInforms(m_adjFileNameList);
        /// ====== 此处对数据进行滤波处理
        filteringRoot();
        /// ====== 显示滤波后的数据
        displayADJFileInform();
    });
}

OBNCalibrationDataDisplay::~OBNCalibrationDataDisplay()
{
    if(0 != m_adjXDataList.count())
    {
        for(int iList = 0; iList < m_adjXDataList.count(); iList ++)
            m_adjXDataList[iList].adjDataList.clear();
    }
    if(0 != m_adjYDataList.count())
    {
        for(int iList = 0; iList < m_adjYDataList.count(); iList ++)
            m_adjYDataList[iList].adjDataList.clear();
    }
    if(0 != m_adjZDataList.count())
    {
        for(int iList = 0; iList < m_adjZDataList.count(); iList ++)
            m_adjZDataList[iList].adjDataList.clear();
    }
    delete ui;
}

void OBNCalibrationDataDisplay::readADJFileInforms(const QStringList & _adjFileList)
{
    /// ======
    if(0 != m_adjXDataList.count())
    {
        for(int iLst = 0; iLst < m_adjXDataList.count(); ++ iLst)
        {
            m_adjXDataList[iLst].adjDataList.clear();
        }
        m_adjXDataList.clear();
    }

    if(0 != m_adjYDataList.count())
    {
        for(int iLst = 0; iLst < m_adjYDataList.count(); ++ iLst)
        {
            m_adjYDataList[iLst].adjDataList.clear();
        }
        m_adjYDataList.clear();
    }

    if(0 != m_adjZDataList.count())
    {
        for(int iLst = 0; iLst < m_adjZDataList.count(); ++ iLst)
        {
            m_adjZDataList[iLst].adjDataList.clear();
        }
        m_adjZDataList.clear();
    }
    /// ======
    QString     readADJLineInfrom;
    QStringList nAdjDataInformList;
    int nCurrentPointNo = 0;
    for(int iList = 0; iList < _adjFileList.count(); iList ++)
    {
        QFile fileRead;
        fileRead.setFileName(_adjFileList[iList]);

        QFileInfo fileInfo(_adjFileList[iList]);

        QColor nColor = QColor::fromRgb(rand()%256,rand()%256,rand()%256);;

        ADJDispInform nCurentADJXName;
        nCurentADJXName.adjName    = fileInfo.fileName();
        nCurentADJXName.nLineColor = nColor;


        ADJDispInform nCurentADJYName;
        nCurentADJYName.adjName    = fileInfo.fileName();
        nCurentADJYName.nLineColor = nColor;

        ADJDispInform nCurentADJZName;
        nCurentADJZName.adjName    = fileInfo.fileName();
        nCurentADJZName.nLineColor = nColor;

        if(fileRead.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            nCurrentPointNo = 0;

            QTextStream in(&fileRead);
            while(!in.atEnd())
            {
                readADJLineInfrom = in.readLine().trimmed().replace(QRegExp("[\\s]+"), " ");

                nCurrentPointNo += 1;

                if(500 > nCurrentPointNo)
                    continue;

                if(2000 < nCurrentPointNo)
                    break;

                nAdjDataInformList = readADJLineInfrom.split(" ");
                if(3 > nAdjDataInformList.count())
                {
                    continue;
                }

                ADJPointDataInform xPointInform;
                xPointInform.dataNumber = nAdjDataInformList[0].toDouble();
                xPointInform.isZeroCorss= false;
                nCurentADJXName.adjDataList.append(xPointInform);

                ADJPointDataInform yPointInform;
                yPointInform.dataNumber = nAdjDataInformList[1].toDouble();
                yPointInform.isZeroCorss= false;
                nCurentADJYName.adjDataList.append(yPointInform);


                ADJPointDataInform zPointInform;
                zPointInform.dataNumber = nAdjDataInformList[2].toDouble();
                zPointInform.isZeroCorss= false;
                nCurentADJZName.adjDataList.append(zPointInform);
            }
            fileRead.close();
        }
        m_adjXDataList.append(nCurentADJXName);
        m_adjYDataList.append(nCurentADJYName);
        m_adjZDataList.append(nCurentADJZName);
    }

    QList<QColor> nColorList;
#if 0
    QString color1("FF6633");
    QColor qColor1(color1.toUInt(NULL,16));
    nColorList << qColor1;

    QString color2("003DF5");
    QColor qColor2(color2.toUInt(NULL,16));
    nColorList << qColor2;

    QString color3("33FF66");
    QColor qColor3(color3.toUInt(NULL,16));
    nColorList << qColor3;
#else
    for(int iList = 0; iList < m_adjXDataList.count(); iList ++)
    {
        QColor nTempColor = m_adjXDataList[iList].nLineColor;
        nColorList.append(nTempColor);
    }
#endif
    /// ====== X
    m_chartXDisplay = new OBNCalibratonDataChart("X");
    connect(m_chartXDisplay, &OBNCalibratonDataChart::signalRightButtonDoubleClick, this, [=](){
        OBNADJDataList* n_adjXInfomList = new OBNADJDataList(this);
        n_adjXInfomList->setCurrentDataVector(m_adjXDataList, m_adjYDataList, m_adjZDataList);
        n_adjXInfomList->show();
    });

    m_chartXDisplay->setAxis(m_adjXDataList.count(), tr(""), 0, 100, 10, tr(""), 0, 100, 10, nColorList);
    QHBoxLayout* nchartXLayout = new QHBoxLayout;
    nchartXLayout->setContentsMargins(0,0,0,0);
    nchartXLayout->addWidget(m_chartXDisplay);
    ui->widgetX->setLayout(nchartXLayout);

    /// ====== Y
    m_chartYDisplay = new OBNCalibratonDataChart("Y");
    connect(m_chartYDisplay, &OBNCalibratonDataChart::signalRightButtonDoubleClick, this, [=](){
        OBNADJDataList* n_adjYInfomList = new OBNADJDataList(this);
        n_adjYInfomList->setCurrentDataVector(m_adjXDataList, m_adjYDataList, m_adjZDataList);
        n_adjYInfomList->show();
    });
    m_chartYDisplay->setAxis(m_adjYDataList.count(), tr(""), 0, 100, 10, tr(""), 0, 100, 10, nColorList);
    QHBoxLayout* nchartYLayout = new QHBoxLayout;
    nchartYLayout->setContentsMargins(0,0,0,0);
    nchartYLayout->addWidget(m_chartYDisplay);
    ui->widgetY->setLayout(nchartYLayout);

    /// ====== Z
    m_chartZDisplay = new OBNCalibratonDataChart("Z");
    connect(m_chartZDisplay, &OBNCalibratonDataChart::signalRightButtonDoubleClick, this, [=](){
        OBNADJDataList* n_adjZInfomList = new OBNADJDataList(this);
        n_adjZInfomList->setCurrentDataVector(m_adjXDataList, m_adjYDataList, m_adjZDataList);
        n_adjZInfomList->show();
    });
    m_chartZDisplay->setAxis(m_adjZDataList.count(), tr(""), 0, 100, 10, tr(""), 0, 100, 10, nColorList);
    QHBoxLayout* nchartZLayout = new QHBoxLayout;
    nchartZLayout->setContentsMargins(0,0,0,0);
    nchartZLayout->addWidget(m_chartZDisplay);
    ui->widgetZ->setLayout(nchartZLayout);
}

void OBNCalibrationDataDisplay::displayADJFileInform()
{
    if(0 == m_adjXDataList.count() ||
       0 == m_adjYDataList.count() ||
       0 == m_adjZDataList.count())
    {
        return;
    }

    int   n_dataNumber = 0;
    qreal min = 9999, max = -9999;
    QList<QList<PointInform>> pointXFListInform, pointYFListInform, pointZFListInform;
    getRange(m_adjXDataList, min, max, n_dataNumber, pointXFListInform);
    m_chartXDisplay->setAxisCurrentYName("X");
    m_chartXDisplay->setCurrentDataRange(0, n_dataNumber, min, max);
    m_chartXDisplay->setCurrentLogData(pointXFListInform);

    getRange(m_adjYDataList, min, max, n_dataNumber, pointYFListInform);
    m_chartYDisplay->setAxisCurrentYName("Y");
    m_chartYDisplay->setCurrentDataRange(0, n_dataNumber, min, max);
    m_chartYDisplay->setCurrentLogData(pointYFListInform);

    getRange(m_adjZDataList, min, max, n_dataNumber, pointZFListInform);
    m_chartZDisplay->setAxisCurrentYName("Z");
    m_chartZDisplay->setCurrentDataRange(0, n_dataNumber, min, max);
    m_chartZDisplay->setCurrentLogData(pointZFListInform);

    /// ====== 释放X空间
    for(int iList = 0; iList < pointXFListInform.count(); iList ++)
    {
        pointXFListInform[iList].clear();
    }
    pointXFListInform.clear();
    /// ====== 释放Y空间
    for(int iList = 0; iList < pointYFListInform.count(); iList ++)
    {
        pointYFListInform[iList].clear();
    }
    pointYFListInform.clear();
    /// ====== 释放Z空间
    for(int iList = 0; iList < pointZFListInform.count(); iList ++)
    {
        pointZFListInform[iList].clear();
    }
    pointZFListInform.clear();
}


void OBNCalibrationDataDisplay::getRange(QList<ADJDispInform> _adjDispInform, qreal& _min, qreal& _max, int& _dtNumMax, QList<QList<PointInform>>& pListPointfList)
{
    _min        = _adjDispInform[0].adjDataList[0].dataNumber;
    _max        = _adjDispInform[0].adjDataList[0].dataNumber;
    _dtNumMax   = _adjDispInform[0].adjDataList.count();
    for(int iList = 0; iList < _adjDispInform.count(); iList ++)
    {
        _dtNumMax   = qMax(_dtNumMax, _adjDispInform[iList].adjDataList.count());

        QList<PointInform> nPointListOfLine;
        for(int jList = 0; jList < _adjDispInform[iList].adjDataList.count(); jList ++)
        {
            _min = qMin(_min, _adjDispInform[iList].adjDataList[jList].dataNumber);
            _max = qMax(_max, _adjDispInform[iList].adjDataList[jList].dataNumber);

            PointInform nPointInform;
            nPointInform.isZeroCorss = _adjDispInform[iList].adjDataList[jList].isZeroCorss;
            nPointInform.nPointInfom.setX(jList);
            nPointInform.nPointInfom.setY(_adjDispInform[iList].adjDataList[jList].dataNumber);
            nPointListOfLine.append(nPointInform);
        }
        pListPointfList.append(nPointListOfLine);
    }
    _min -= 1000;
    _max += 1000;
}

/// ====== 滤波
void OBNCalibrationDataDisplay::filteringRoot()
{
    if(0 == m_adjXDataList.count() ||
       0 == m_adjYDataList.count() ||
       0 == m_adjZDataList.count())
    {
        return;
    }

    int nCurentDataNum = m_adjXDataList[0].adjDataList.count();
    double* nDataInput  = new double[nCurentDataNum];
    double* nDataOutput = new double[nCurentDataNum];

    /// ====== X方向
    for(int iList = 0; iList < m_adjXDataList.count(); iList ++)
    {
        memset (nDataInput,  0, nCurentDataNum * sizeof(double));
        memset (nDataOutput, 0, nCurentDataNum * sizeof(double));
        for(int iListNo = 0; iListNo < nCurentDataNum; iListNo ++)
        {
            nDataInput[iListNo] = m_adjXDataList[iList].adjDataList[iListNo].dataNumber;
        }
        BiDirectionalFilter(nDataInput, nDataOutput, nCurentDataNum);
        for(int iListNo = 0; iListNo < nCurentDataNum; iListNo ++)
        {
            double xFilterAfter = nDataOutput[iListNo];
            m_adjXDataList[iList].adjDataList[iListNo].dataNumber = xFilterAfter;
        }
    }
    /// ====== 查找X方向数据过零点
    queryDataZeroCross(m_adjXDataList);

    /// ====== Y方向
    for(int iList = 0; iList < m_adjYDataList.count(); iList ++)
    {
        memset (nDataInput,  0, nCurentDataNum * sizeof(double));
        memset (nDataOutput, 0, nCurentDataNum * sizeof(double));
        for(int iListNo = 0; iListNo < nCurentDataNum; iListNo ++)
        {
            nDataInput[iListNo] = m_adjYDataList[iList].adjDataList[iListNo].dataNumber;
        }
        BiDirectionalFilter(nDataInput, nDataOutput, nCurentDataNum);
        for(int iListNo = 0; iListNo < nCurentDataNum; iListNo ++)
        {
            double yFilterAfter = nDataOutput[iListNo];
            m_adjYDataList[iList].adjDataList[iListNo].dataNumber = yFilterAfter;
        }
    }
    /// ====== 查找Y方向数据过零点
    queryDataZeroCross(m_adjYDataList);

    /// ====== Z方向
    for(int iList = 0; iList < m_adjZDataList.count(); iList ++)
    {
        memset (nDataInput,  0, nCurentDataNum * sizeof(double));
        memset (nDataOutput, 0, nCurentDataNum * sizeof(double));
        for(int iListNo = 0; iListNo < nCurentDataNum; iListNo ++)
        {
            nDataInput[iListNo] = m_adjZDataList[iList].adjDataList[iListNo].dataNumber;
        }
        BiDirectionalFilter(nDataInput, nDataOutput, nCurentDataNum);
        for(int iListNo = 0; iListNo < nCurentDataNum; iListNo ++)
        {
            double zFilterAfter = nDataOutput[iListNo];
            m_adjZDataList[iList].adjDataList[iListNo].dataNumber = zFilterAfter;
        }
    }
    /// ====== 查找Z方向数据过零点
    queryDataZeroCross(m_adjZDataList);

    delete [] nDataInput;
    delete [] nDataOutput;
}


/// ====== 查询当前数据过零点
bool OBNCalibrationDataDisplay::queryDataZeroCross(QList<ADJDispInform>& _adjDataList)
{
    int n_adjDataLenghtMax = 0;
    for(int iList = 0; iList < _adjDataList.count(); iList ++)
    {
        n_adjDataLenghtMax = qMax(n_adjDataLenghtMax, _adjDataList[iList].adjDataList.count());
    }

    double n_adjDataMin  = 0.0, n_adjDataMax = 0.0;
    int    n_adjDataMinLocat=0, n_adjDataMaxLocat = 0;
    double * n_adjData = new double[n_adjDataLenghtMax];
    for(int iList = 0; iList < _adjDataList.count(); iList ++)
    {
        memset(n_adjData, 0, n_adjDataLenghtMax*sizeof(double));
        /// ====== 查找最低点
        if(0 >= _adjDataList[iList].adjDataList.count())
        {
            continue;
        }

        /// ====== 获取最低点位置
        n_adjDataMin    = _adjDataList[iList].adjDataList[0].dataNumber;
        n_adjDataMax    = _adjDataList[iList].adjDataList[0].dataNumber;
        n_adjDataMinLocat = 0;
        n_adjDataMaxLocat = 0;
        for(int iData = 1; iData < _adjDataList[iList].adjDataList.count(); iData ++)
        {
            /// ======
            if(n_adjDataMin > _adjDataList[iList].adjDataList[iData].dataNumber)
            {
                n_adjDataMin  = _adjDataList[iList].adjDataList[iData].dataNumber;
                n_adjDataMinLocat= iData;
            }
            /// ======
            if(n_adjDataMax < _adjDataList[iList].adjDataList[iData].dataNumber)
            {
                n_adjDataMax = _adjDataList[iList].adjDataList[iData].dataNumber;
                n_adjDataMaxLocat = iData;
            }
        }
        _adjDataList[iList].dampingInform = n_adjDataMax/n_adjDataMin;  ///< 计算阻尼信息
        _adjDataList[iList].cycleInform   = 100.0f/((n_adjDataMaxLocat-n_adjDataMinLocat)/2);

        /// ====== 获取最低点之前的数据
        n_adjDataMinLocat -= 1;
        for(int iDataNO = 0; iDataNO < n_adjDataMinLocat; iDataNO ++)
        {
            n_adjData[iDataNO] = _adjDataList[iList].adjDataList[iDataNO].dataNumber;
        }

        /// ====== 获取当前数据列表平均值
        double n_sumAdjData = 0.0;
        for(int iDataNo = 0; iDataNo < n_adjDataMinLocat; iDataNo ++)
        {
            n_sumAdjData += n_adjData[iDataNo];
        }
        double n_averageAdjValue = n_sumAdjData / n_adjDataMinLocat;

        /// ====== 减去平均值
        for(int iDataNo = 0; iDataNo < n_adjDataMinLocat; iDataNo ++)
        {
            n_adjData[iDataNo] -= n_averageAdjValue;
        }

        /// ====== 获取当前过零点位置
        int n_zeroCorssLocat = n_adjDataMinLocat;
        for(int iNO = n_adjDataMinLocat; iNO > 0; iNO --)
        {
            if(0 > n_adjData[iNO]*n_adjData[iNO-1])
            {
                n_zeroCorssLocat = iNO;
                break;
            }
        }
        _adjDataList[iList].adjDataList[n_zeroCorssLocat].isZeroCorss = true;
        _adjDataList[iList].n_zeroCrossNum = n_zeroCorssLocat;
    }
    delete [] n_adjData; n_adjData = NULL;
    return true;
}

void OBNCalibrationDataDisplay::BiDirectionalFilter(const double * sig, double * sout, const int data_len)
{
    double* tmp1 = new double[data_len];
    double* tmp2 = new double[data_len];
    FiltData(sig, tmp1, data_len);
    dataRollingOver(tmp1, tmp2, data_len);
    FiltData(tmp2, tmp1, data_len);
    dataRollingOver(tmp1, sout, data_len);
    delete[]tmp1;
    delete[]tmp2;
}

void OBNCalibrationDataDisplay::dataRollingOver(const double * sig,double * sout,const int data_len)
{
    for (int i = 0; i < data_len; i++)
    {
        sout[data_len - i-1] = sig[i];
    }
}

int OBNCalibrationDataDisplay::signalExtend(const double *sig, double * sout, const int data_len, const int nfact)
{
    for (int i = 0; i < nfact; i++)
    {
        sout[i] = sig[nfact - i];
    }
    for (int i = nfact; i < data_len+ nfact; i++)
    {
        sout[i] = sig[i- nfact];
    }
    return data_len + nfact;
}

void OBNCalibrationDataDisplay::FiltData(const double * sig, double * sout,const int data_len)
{
    int N = myfilter.len;
    int nfact = 2 * (N - 1);
    //信号延拓
    double* s_ext = new double[data_len + nfact];	// 延拓后的输入信号
    double* tmps = new double[data_len + nfact];	// 作为处理过程中的输出信号
    int data_len_ext = signalExtend(sig, s_ext, data_len, nfact);
    for (int i = 0; i < data_len_ext; i++)
    {
        tmps[i] = s_ext[i];
    }
    for (int i = N; i < data_len_ext; i++)
    {
        double tmp = 0;
        for (int j = 0; j < N; j++)
        {
            tmp += myfilter.b[j] * s_ext[i - j];
        }
        for (int j = 1; j < N; j++)
        {
            tmp -= myfilter.a[j] * tmps[i - j];
        }
        tmps[i] = tmp;
        //printf("out[%d]=%f\n",i, tmp);
    }
    //输出
    for (int i = 0; i < data_len; i++)
    {
        sout[i] = tmps[i + nfact];
    }
    delete[]tmps;
    delete[]s_ext;
}










