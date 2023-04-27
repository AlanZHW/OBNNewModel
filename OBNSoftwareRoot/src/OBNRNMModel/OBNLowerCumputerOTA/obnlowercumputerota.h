#ifndef OBNLOWERCUMPUTEROTA_H
#define OBNLOWERCUMPUTEROTA_H

#include <QLabel>
#include <QDebug>
#include <QWidget>
#include <QCheckBox>
#include <QTextStream>
#include <QProgressBar>
#include <QFileDialog>
#include <QFileInfoList>

#include "macro.h"
#include "publicHostInform.h"
#include "qftp.h"
#include "obnretrieveavailablenodes.h"
#include "obnlowercumputerota_global.h"

#include "obnotanode.h"


typedef struct {
    QString _name;
    QString _value;
    QString _explain;
}CFGInform;

QT_BEGIN_NAMESPACE
namespace Ui { class OBNLowerCumputerOTA; }
QT_END_NAMESPACE

class OBNOTA_EXPORT OBNLowerCumputerOTA : public QDialog
{
    Q_OBJECT
public:
    OBNLowerCumputerOTA(QWidget *parent = nullptr);
    ~OBNLowerCumputerOTA();
    void setCurrentOptionalInform(const QVector<HostsState>&);
    /// ======升级选项修改
    void otaOptionIndexChange(const int&);

    /// ====== 开始执行配置文件修改工作
    void startChangeConfigFileFunction();       ///<
    void getCurentChangeIDAlsoGetConfigFile();  ///<
    void readCurrentConfigFileFunction(int, const QString&);
    /// ====== 读取配置文件内容
    void readConfigInformFunction(const QString& _configName, QList<CFGInform>& _configInformList);
    /// ====== 修改文件内容并存储到磁盘
    void updateCurrentConfigFileFunction(const QString& _uploadFName, QList<CFGInform>& _configInformList);
    /// ====== 上传新的配置文件
    void putCurrentConfigFileFunction(const int _row, const QString& n_uploadfName, const QString& _nodefName);
    /// ======
    void initConfigTableInfrom(int row, const QString& _configfName);

    /// ====== 上传升级文件
    void putUpgradeFilesFunctio(const QString& _otaFileName, const QString &_nodefName);
signals:
    void sig_startWork();   ///< 开始升级

private slots:
    /// ====== 升级选项调整
    void slotOTAOptionComboBoxIndexChange(const int&);
    /// ====== 升级成功
    void slotOTAErrorFunction(int, QString);
    /// ======
    void slotOTAGetConfigFileSuccess(int, const QString&);
    /// ======
    void slotPutOTAFileSuccess(int);
    /// ======
    void slotCurrentProgress(int, int);
    /// ======
    void slotNodeTableCheckBoxStateChange(int);
private:
    QString m_fileName;
    QString m_connectedStyle, m_disConnectedStyle;
    QVector<HostsState> m_hostVertor;
    ONBRetrieveAvailableNodes* m_obnSeatchHosts;
    /// ======
    int         m_curentNodeNum;
    OBNOtaNode* m_curentNodes;
    /// ====== 当前主机工作目录,用于存放config文件
    QString m_currentWorkPath;
    QString m_currentConfigFileName;
    /// ====== 目标主机config文件名
    QString m_curentHostConfigFileName;
    /// ======
    QString m_hostPath;
    bool    m_startUpload;
    QList<int> m_curentSelectedNodeList;    ///< 当前选中的节点列表

    /// ======
    QString m_currentFileName, m_curentNodefName;

    Ui::OBNLowerCumputerOTA *ui;
};
#endif // OBNLOWERCUMPUTEROTA_H
