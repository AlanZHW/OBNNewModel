#include "readcalibationdata.h"

/************************************************************************************
    Function    : void detrend_IP(T *y, T *x, int m)
    Description : Remove the linear trend of the input floating point data. Note that this
                  will initialize a work buffer inside the function. So if you are calling
                  this many, many times, create your work buffer in the calling scope and call
                  detrend(T *y, T*x, int m) instead to avoid initializing memory over and over
                  again.
    Inputs      : y - Floating point input data
                 m - Input data length
    Outputs     : y - Data with linear trend removed
    Copyright   : DSO National Laboratories
    History     : 01/02/2008, TCK, Adapted from HYC code
                  01/12/2008, TCK, Added in return value
                  25/01/2016, Pier, Changed into template type, removed need for work buffer
    *************************************************************************************/
template<typename T>
void detrend_IP(T *y, int m)
{
    T xmean, ymean;
    int i;
    T temp;
    T Sxy;
    T Sxx;

    T grad;
    T yint;

    std::unique_ptr<T[]> x(new T[m]);

    /********************************
    Set the X axis Liner Values
    *********************************/
    for (i = 0; i < m; i++)
        x[i] = i;

    /********************************
    Calculate the mean of x and y
    *********************************/
    xmean = 0;
    ymean = 0;
    for (i = 0; i < m; i++)
    {
        xmean += x[i];
        ymean += y[i];
    }
    xmean /= m;
    ymean /= m;

    /********************************
    Calculate Covariance
    *********************************/
    temp = 0;
    for (i = 0; i < m; i++)
        temp += x[i] * y[i];
    Sxy = temp / m - xmean * ymean;

    temp = 0;
    for (i = 0; i < m; i++)
        temp += x[i] * x[i];
    Sxx = temp / m - xmean * xmean;

    /********************************
    Calculate Gradient and Y intercept
    *********************************/
    grad = Sxy / Sxx;
    yint = -grad * xmean + ymean;

    /********************************
    Removing Linear Trend
    *********************************/
    for (i = 0; i < m; i++)
        y[i] = y[i] - (grad * i + yint);
}

/// ====== 求数据平均数
template<typename T>
T average_value(T* data, int m)
{
    int data_no = 0;
    T   data_sum= 0;
    for(; data_no <= m; data_no ++)
    {
        data_sum += data[data_no];
    }
    return data_sum/m;
}

/// ====== 数组数据减掉一个数
template<typename T>
void minus_value(T* data, T m, int num)
{
    for(int dtno = 0; dtno <= num; dtno ++)
        data[dtno] -= m;
}

/// ====== 求数据最大值,并返回最大值和最大值的位置
template<typename T>
void maxf(T* data, int num, T max_value, int max_locat)
{
    max_value = data[0];
    max_locat = 0;
    for(int dtno = 1; dtno < num; dtno ++)
    {
        if(data[dtno] > max_value)
        {
            max_value = data[dtno];
            max_locat = dtno;
        }
    }
}

/// ====== 求数据最小值,并返回最大值和最小值的位置
template<typename T>
void minf(T* data, int num, T min_value, int min_locat)
{
    min_value = data[0];
    min_locat = 0;
    for(int dtno = 1; dtno < num; dtno ++)
    {
        if(data[dtno] < min_value)
        {
            min_value = data[dtno];
            min_locat = dtno;
        }
    }
}

ReadCalibationData::ReadCalibationData(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<QVector<ADJDispInform>>("QVector<ADJDispInform>");//注册diskInformation类型
    qRegisterMetaType<ADJAllDataInform>("ADJAllDataInform");//注册diskInformation类型

    //fs=100,fc=10hz,5阶,butterworth-IIR型低通滤波器
    myfilter.len = 6;
    myfilter.a << 1 << -2.75244113481752 << 3.33871807933893 << -2.13725305171939 << 0.713552009831375 << -0.0984430331073669;
    myfilter.b << 0.00200415217268850 << 0.0100207608634425 << 0.0200415217268850 << 0.0200415217268850 << 0.0100207608634425 << 0.00200415217268850;

}

/// ====== 读取Adj文件内容
void ReadCalibationData::slotReadCalibationDataFunction(int _calibrationDtMode, const QStringList& _AdjFileNameList)
{
    switch (_calibrationDtMode)
    {
    case 0:
        readCalibationDataFunctionFromOBN(_AdjFileNameList);
        break;
    case 1:
        readCalibationDataFunctionFromCDS(_AdjFileNameList);
        break;
    default:
        break;
    }
}

/// ====== 读取OBN模式标定数据文件
void ReadCalibationData::readCalibationDataFunctionFromOBN(const QStringList& _fimeNameList)
{
    QVector<ADJDispInform> n_adjXDataList, n_adjYDataList, n_adjZDataList;
    /// ======
    QString     readADJLineInfrom;
    QStringList nAdjDataInformList;
    int nCurrentPointNo = 0;
    for(int iList = 0; iList < _fimeNameList.count(); iList ++)
    {
        QFile fileRead;
        fileRead.setFileName(_fimeNameList[iList]);

        QFileInfo fileInfo(_fimeNameList[iList]);

        QColor nColor = QColor::fromRgb(rand()%256,rand()%256,rand()%256);

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
        n_adjXDataList.append(nCurentADJXName);
        n_adjYDataList.append(nCurentADJYName);
        n_adjZDataList.append(nCurentADJZName);
    }
    /// ====== 增加滤波计算以及过零点查找
    filteringFunction(n_adjXDataList);
    filteringFunction(n_adjYDataList);
    filteringFunction(n_adjZDataList);

    ADJAllDataInform m_allDataInform;
    emit signal_current_adj_data_inform(n_adjXDataList, n_adjYDataList, n_adjZDataList, m_allDataInform);
}

/// ====== 读取CDS模式标定数据文件
void ReadCalibationData::readCalibationDataFunctionFromCDS(const QStringList& _fimeNameList)
{
    QVector<ADJDispInform> n_adjXDataList, n_adjYDataList, n_adjZDataList;
    /// ======
    QString     readADJLineInfrom;
    QStringList nAdjDataInformList;
    int nCurrentPointNo = 0;
    for(int iList = 0; iList < _fimeNameList.count(); iList ++)
    {
        QFile fileRead;
        fileRead.setFileName(_fimeNameList[iList]);

        QFileInfo fileInfo(_fimeNameList[iList]);

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
        n_adjXDataList.append(nCurentADJXName);
        n_adjYDataList.append(nCurentADJYName);
        n_adjZDataList.append(nCurentADJZName);
    }

    /// ====== 增加计算线型去趋势
    adjDataDetrendFunction(n_adjXDataList); ///< X
    adjDataDetrendFunction(n_adjYDataList); ///< Y
    adjDataDetrendFunction(n_adjZDataList); ///< Z

    /// ====== 阻尼计算
    smalldampCalculation(n_adjXDataList);
    smalldampCalculation(n_adjYDataList);
    smalldampCalculation(n_adjZDataList);

    ADJAllDataInform m_allDataInform;
    /// ====== 获取ADJ所有点平均值和标准差
    allDataParticipatedCalculations(n_adjXDataList, m_allDataInform.x_component);
    allDataParticipatedCalculations(n_adjYDataList, m_allDataInform.y_component);
    allDataParticipatedCalculations(n_adjZDataList, m_allDataInform.z_component);

    emit signal_current_adj_data_inform(n_adjXDataList, n_adjYDataList, n_adjZDataList, m_allDataInform);
}

/// ====== 计算获取当前数据的平均值和标准差
void ReadCalibationData::allDataParticipatedCalculations(QVector<ADJDispInform> _adjDataInformVector, ADJAllDataParameterInform& _ajdAllDataInform)
{
    /// ====== 获取总数据平均值
    double currentDataAverageSum = 0;
    int    currentDataCount      = _adjDataInformVector.count();
    for(int iVector = 0; iVector < currentDataCount; iVector ++)
    {
        currentDataAverageSum += _adjDataInformVector[iVector].relativeFrequency;
    }

    _ajdAllDataInform.averageValue = currentDataAverageSum/currentDataCount;
    qDebug() << "总数据的相对频率de平均值是:" << _ajdAllDataInform.averageValue;

    /// ====== 获取总数据标准差
    double standardDeviationValue = 0;
    int    standardDeviationNumber= currentDataCount-1;
    for(int iVector = 0; iVector < currentDataCount; iVector ++)
    {
        standardDeviationValue += pow(_adjDataInformVector[iVector].relativeFrequency -_ajdAllDataInform.averageValue, 2);
    }
    _ajdAllDataInform.standardDeviation = sqrt(standardDeviationValue/standardDeviationNumber);
    qDebug() << "标准差 = " << _ajdAllDataInform.standardDeviation;
    /// ====== 相对标准偏差
    _ajdAllDataInform.standardDeviation = (_ajdAllDataInform.standardDeviation/_ajdAllDataInform.averageValue)*100.0f;
    qDebug() << "总数据的相对标准差是:" << _ajdAllDataInform.standardDeviation;
}

/// ====== 阻尼计算
void ReadCalibationData::smalldampCalculation(QVector<ADJDispInform>& _adjDisplayInformVector)
{
    /// ====== 用于存储第一个过零点和第二个过零点的位置
    int firstZCrossLocat  = 0;  ///< 第一个过零点的位置
    int secondZCrossLocat = 0;  ///< 第二个过零点的位置
    double  minDataNumber= 0.0, maxDataNumber = 0.0;    ///< 当前道数据最小值,最大值
    int     minDataLocat = 0, maxDataLocat    = 0;      ///< 当前数据最小值位置和最大值位置
    double A1, A2, Bt;
    double t1, t2, t0, T;
    float  y, Bt0, Fn, Fn0;
    int    calculatorLeft = 0, calculatorRight = 0;
    for(int iVector = 0; iVector < _adjDisplayInformVector.count(); iVector ++)
    {
        calculatorLeft = 0;
        calculatorRight= 0;

        /// ====== 先获取最大值所在位置
        queryExtremumFunction(_adjDisplayInformVector[iVector].adjDataList, 0, _adjDisplayInformVector[iVector].adjDataList.count()-1,  maxDataLocat, maxDataNumber);
        qDebug() << "maxDataLocat = " << maxDataLocat << "\t maxDataNumber = " << maxDataNumber;

        /// ====== 在最大值范围内获取过零点
        calculatorRight = maxDataLocat - 1;
        qDebug() << "calculatorRight = " << calculatorRight;
        firstZCrossLocat = queryDataZeroCrossLine(_adjDisplayInformVector[iVector].adjDataList, calculatorLeft, calculatorRight);
        _adjDisplayInformVector[iVector].n_zeroCrossNum = firstZCrossLocat;
        _adjDisplayInformVector[iVector].adjDataList[firstZCrossLocat].isZeroCorss = true;
        qDebug() << "第一个过零点的位置: " << firstZCrossLocat << "\t" << _adjDisplayInformVector[iVector].adjDataList[firstZCrossLocat].dataNumber;

        A1 = fabs(maxDataNumber)-_adjDisplayInformVector[iVector].adjDataList[firstZCrossLocat].dataNumber;
        t1 = (maxDataLocat-firstZCrossLocat)/100.0f;
        qDebug() << "A1 = " << A1 << "\t t1 = " << t1;

        /// ====== 找最小点位置
        queryExtremumMinFunction(_adjDisplayInformVector[iVector].adjDataList, maxDataLocat, _adjDisplayInformVector[iVector].adjDataList.count()-1,  minDataLocat, minDataNumber);
        qDebug() << "minDataLocat = " << minDataLocat << "\t minDataNumber = " << minDataNumber;

        A2 = fabs(minDataNumber-_adjDisplayInformVector[iVector].adjDataList[firstZCrossLocat].dataNumber);
        t2 = (minDataLocat-firstZCrossLocat)/100.0f;
        qDebug() << "A2 = " << A2 << "\t t2 = " << t2;

        Bt = log(A1/A2)/sqrt(pow(m_pi, 2) + pow(log(A1/A2), 2));
        qDebug() << "Bt = " << Bt;

        /// ====== 寻找第2个过零点位置
        calculatorLeft = maxDataLocat;
        calculatorRight= _adjDisplayInformVector[iVector].adjDataList.count()-1;
        secondZCrossLocat = queryDataZeroCrossLine(_adjDisplayInformVector[iVector].adjDataList, calculatorLeft, calculatorRight);
        secondZCrossLocat = secondZCrossLocat + calculatorLeft;
        qDebug() << "secondZCrossLocat = " << secondZCrossLocat;
        double tempLocat = secondZCrossLocat-firstZCrossLocat;
        T = tempLocat/100.0f;
        qDebug() << "T = " << T;
        t0 = T;
        y  = t1/t0;
        qDebug() << "y = " << y;
        Bt0 = cos(y*m_pi);  ///< 阻尼
        _adjDisplayInformVector[iVector].dampingInform = Bt0;
        Fn  = 1/(2*sqrt(1-pow(Bt, 2))*t0);  ///<
        Fn0 = 1/(2*sqrt(1-pow(Bt0, 2))*t0); ///< 频率
        qDebug() << "Bt0 = " << Bt0 << "\t Fn = " << Fn << "\t Fn0 = " << Fn0;
        _adjDisplayInformVector[iVector].relativeFrequency = Fn0;

        _adjDisplayInformVector[iVector].relativeError = fabs((Fn0-0.05)/0.05*100);
        qDebug() << "relativeError = " << _adjDisplayInformVector[iVector].relativeError;

        /// ====== 计算单条曲线的平均值
        int nCurrentDataNum = _adjDisplayInformVector[iVector].adjDataList.count();
        double* m_dataArrayAll = new double[nCurrentDataNum];
        for(int iList = 0; iList < nCurrentDataNum; iList ++)
            m_dataArrayAll[iList] = _adjDisplayInformVector[iVector].adjDataList[iList].dataNumber;
        _adjDisplayInformVector[iVector].averageValue = average_value(m_dataArrayAll, nCurrentDataNum-1);
        delete [] m_dataArrayAll; m_dataArrayAll = NULL;
    }
}

/// ====== 获取最大值,最大值位置
void ReadCalibationData::queryExtremumFunction(QVector<ADJPointDataInform> _adjDataInfromList, int _left, int _right, int& _maxLocat, double& _maxValue)
{
    _maxLocat = _left;
    _maxValue = _adjDataInfromList[_left].dataNumber;
    for(int iNO = _left+1; iNO <= _right; iNO ++)
    {
        if(_maxValue < _adjDataInfromList[iNO].dataNumber)
        {
            _maxValue = _adjDataInfromList[iNO].dataNumber;
            _maxLocat = iNO;
        }
    }
}

/// ====== 获取最小值,最小值位置
void ReadCalibationData::queryExtremumMinFunction(QVector<ADJPointDataInform> _adjDataInfromList, int _left, int _right, int& _minLocat, double& _minValue)
{
    _minLocat = _left;
    _minValue = _adjDataInfromList[_left].dataNumber;
    for(int iNO = _left+1; iNO <= _right; iNO ++)
    {
        if(_minValue > _adjDataInfromList[iNO].dataNumber)
        {
            _minValue = _adjDataInfromList[iNO].dataNumber;
            _minLocat = iNO;
        }
    }
}

/// ====== 寻找第一个过零点位置
//int ReadCalibationData::firstZeroCrossLocatFunction(ADJDispInform& _adjDataInfrom)
//{
//    for(int iList = 0; iList < _adjDataInfrom.adjDataList.count(); iList ++)
//    {
//        if(_adjDataInfrom.adjDataList[iList].isZeroCorss)
//            return iList;
//    }
//    return 0;
//}
/// ====== 寻找第二个过零点的位置
//int ReadCalibationData::secondZeroCrossLocatFunction(ADJDispInform& _adjDataInfrom)
//{
//    bool flag = false;
//    for(int iList = 0; iList < _adjDataInfrom.adjDataList.count(); iList ++)
//    {
//        if(_adjDataInfrom.adjDataList[iList].isZeroCorss)
//        {
//            if(flag)
//            {
//                return iList;
//            }
//            else
//            {
//                flag = true;
//            }
//        }
//    }
//    return 0;
//}

/// ====== 调用线性去趋势计算函数
void ReadCalibationData::adjDataDetrendFunction(QVector<ADJDispInform> & _adjPointInform)
{
    for(int iList = 0; iList < _adjPointInform.count(); iList ++)
    {
        int n_adjZDataNum = _adjPointInform[iList].adjDataList.count();

        double* n_adjZDataBuff = new double[n_adjZDataNum];
        for(int iData = 0; iData < n_adjZDataNum; iData ++)
        {
            n_adjZDataBuff[iData] = _adjPointInform[iList].adjDataList[iData].dataNumber;
        }
        detrend_IP(n_adjZDataBuff, n_adjZDataNum);

        for(int iData = 0; iData < n_adjZDataNum; iData ++)
        {
            _adjPointInform[iList].adjDataList[iData].dataNumber = n_adjZDataBuff[iData];
        }
        delete [] n_adjZDataBuff; n_adjZDataBuff = NULL;
    }
}

/// ====== 过滤
void ReadCalibationData::filteringFunction(QVector<ADJDispInform> & _adjPointInform)
{
    int nCurentDataNum = _adjPointInform[0].adjDataList.count();
    double* nDataInput  = new double[nCurentDataNum];
    double* nDataOutput = new double[nCurentDataNum];
    for(int iList = 0; iList < _adjPointInform.count(); iList ++)
    {
        memset (nDataInput,  0, nCurentDataNum * sizeof(double));
        memset (nDataOutput, 0, nCurentDataNum * sizeof(double));
        for(int iListNo = 0; iListNo < nCurentDataNum; iListNo ++)
        {
            nDataInput[iListNo] = _adjPointInform[iList].adjDataList[iListNo].dataNumber;
        }
        BiDirectionalFilter(nDataInput, nDataOutput, nCurentDataNum);
        for(int iListNo = 0; iListNo < nCurentDataNum; iListNo ++)
        {
            double xFilterAfter = nDataOutput[iListNo];
            _adjPointInform[iList].adjDataList[iListNo].dataNumber = xFilterAfter;
        }
    }
    delete [] nDataInput; nDataInput = NULL;
    delete []  nDataOutput; nDataOutput = NULL;

    /// ====== 查找数据过零点
    queryDataZeroCross(_adjPointInform);
}

/// ====== 单条线获取过零点
int ReadCalibationData::queryDataZeroCrossLine(QVector<ADJPointDataInform> _adjDataInfrom, int _left, int _right)
{
    int n_currentAdjDataLenght = _right-_left+1;

    int    nDataNO = 0;
    double *adjDataArray = new double[n_currentAdjDataLenght];
    for(int iVector = _left; iVector <= _right; iVector ++, nDataNO ++)
    {
        adjDataArray[nDataNO] = _adjDataInfrom[iVector].dataNumber;
    }
    int nfirstZeroPickIndex = 0;
    double curentProduct    = 0;
    for(int iDataNO = n_currentAdjDataLenght-1; iDataNO >= 0; iDataNO --)
    {
        curentProduct = adjDataArray[iDataNO]*adjDataArray[iDataNO+1];
        if(d_min > curentProduct)
        {
            nfirstZeroPickIndex = iDataNO+1;
        }
    }
    delete [] adjDataArray;
    adjDataArray = NULL;
    /// ======
    return nfirstZeroPickIndex;
}

/// ====== 查询当前数据过零点
bool ReadCalibationData::queryDataZeroCross(QVector<ADJDispInform>& _adjDataList)
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
        double n_averageAdjValue = average_value(n_adjData, n_adjDataMinLocat);
        /// ====== 保留当前数据平均值
        _adjDataList[iList].averageValue = n_averageAdjValue;
        /// ====== 减去平均值
        minus_value(n_adjData, n_averageAdjValue, n_adjDataMinLocat);

        /// ====== 获取当前过零点位置
        int n_zeroCorssLocat = n_adjDataMinLocat;
        double curentProduct = 0.0f;
        for(int iNO = n_adjDataMinLocat; iNO > 0; iNO --)
        {
            curentProduct = n_adjData[iNO]*n_adjData[iNO-1];
            if(0 > curentProduct)
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

void ReadCalibationData::BiDirectionalFilter(const double * sig, double * sout, const int data_len)
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

void ReadCalibationData::dataRollingOver(const double * sig,double * sout,const int data_len)
{
    for (int i = 0; i < data_len; i++)
    {
        sout[data_len - i-1] = sig[i];
    }
}

int ReadCalibationData::signalExtend(const double *sig, double * sout, const int data_len, const int nfact)
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

void ReadCalibationData::FiltData(const double * sig, double * sout,const int data_len)
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






















