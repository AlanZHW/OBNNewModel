#ifndef OBNCALIBRATIONDATADISPLAY_H
#define OBNCALIBRATIONDATADISPLAY_H

#include <QDir>
#include <QFile>
#include <QThread>
#include <QDialog>
#include <QString>
#include <QSettings>
#include <QCheckBox>
#include <QTextCodec>
#include <QRadioButton>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QColorDialog>

#include "obncalibratondatachart.h"
#include "obncalibrationdatapublic.h"
#include "obncalibrationdatadisplay_global.h"
#include "readcalibationdata.h"

#include "macro.h"
#include "publicHostInform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class OBNCalibrationDataDisplay; }
QT_END_NAMESPACE

class OBNCALIBRATIONDATADISPLAY_EXPORT OBNCalibrationDataDisplay : public QDialog
{
    Q_OBJECT

public:
    OBNCalibrationDataDisplay(QWidget *parent = nullptr);
    ~OBNCalibrationDataDisplay();
    void setProjectInfrom(const QString&, const QString&);
private:
    void getRange(QVector<ADJDispInform> _adjDispInform, qreal& _min, qreal& _max, int& _dtNumMax, QList<QList<PointInform>>& pListPointfList);
    /// ====== 显示ADJ文件内容
    void displayADJFileInform();

    /// ====== 显示数据颜色设置表格
    void showLineColorTableWidgetFunction(const QVector<ADJDispInform>& _AdjX);
    /// ====== 显示数据信息表格内容
    void showLineInformTableWidgetFunction(const QVector<ADJDispInform>&, const QVector<ADJDispInform>&, const QVector<ADJDispInform>&, ADJAllDataInform&);

signals:
    void signal_read_adj_data(int, const QStringList&);

public slots:
    /// ====== 读取ADJ文件数据信号
    void slotReadAdjFileSuccess(QVector<ADJDispInform>,QVector<ADJDispInform>,QVector<ADJDispInform>, ADJAllDataInform);
    /// ====== 设置数据是否显示
    void slotIsDisplayLineFunction(int);
private:
    QString m_curentProjPath, m_curentProjName;
    QSettings* m_settings;
    int     m_zeroerror, m_freqrelateror, m_stderror;
    /// ======
    QThread* m_readDataThread;
    ReadCalibationData* m_readCalibation;   ///< 读取标定数据文件类
    /// ======
    int m_curentAdjMode;    ///< 描述当前ADJ文件模式
    /// ====== 当前ADJ文件列表
    QStringList m_adjFileNameList;
    QVector<ADJDispInform>  m_adjXDataList, m_adjYDataList, m_adjZDataList;
    OBNCalibratonDataChart* m_chartXDisplay, *m_chartYDisplay, *m_chartZDisplay;
    Ui::OBNCalibrationDataDisplay *ui;
};
#endif // OBNCALIBRATIONDATADISPLAY_H
