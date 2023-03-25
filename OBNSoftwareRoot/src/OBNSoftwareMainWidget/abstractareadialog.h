#ifndef ABSTRACTAREADIALOG_H
#define ABSTRACTAREADIALOG_H

#include <QFrame>
#include <QDebug>
#include <QLabel>
#include <QRegExp>
#include <QDialog>
#include <QGroupBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QMessageBox>
#include <QFileDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QRadioButton>
#include <QRegExpValidator>

#include "publicHostInform.h"

class AbstractAreaDialog : public QDialog
{
    Q_OBJECT
public:
    enum  AreaOption
    {
        CreateArea = 0,
        UpdateArea = 1
    };
    enum UpdateOption
    {
        ReplaceSps = 0,
        MergeSps   = 1
    };

    AbstractAreaDialog(QWidget *parent = nullptr);
    ~AbstractAreaDialog();

    void setProjectInfo(const QString &projPath,const QString &projName)
    {
        m_projInfo.ProjectPath = projPath;
        m_projInfo.ProjectName = projName;
    }
    void setProjectInfo(const ProjectInfo &info)
    {
        m_projInfo = info;
    }
    void setAreaOption(AreaOption option);
    AreaDataInfo *areaDataInfo()const
    {
        return m_AreaDatainfo;
    }
    QString areaName() const
    {
        return  m_areaNameEdt->text();
    }
    QStringList spsFiles() const
    {
        return m_spsFiles;
    }
    AreaOption  areaOption()
    {
        return m_areaOpt;
    }
    UpdateOption updateOption()
    {
        return m_updateOpt;
    }
public slots:
    //进度刷新------------
    void setProgressValue(const int &value);
    //progress hint------
    void setOperateHint(const QString &hint);

    /// ======
    void setProgressInfo(const QString &hint,const int &value)
    {
        /// ====== 设置进度条头信息
        setProgressValue(value);
        /// ====== 设置进度值
        setOperateHint(hint);
    }

protected :
    void setOptBtnText(const QString &text);
    void setAreaEditReadOnly(const bool &);
    void setAreaName(const QString &areaName);
    /// ====== 结果
    QString rFileName() const {return m_RfileEdt->text();}
    QString sFileName() const {return m_SfileEdt->text();}
    QString xFileName() const {return m_XfileEdt->text();}


protected slots:
    void slotBrowserSPSFile();
    void slotOperate();
    void slotReplaceUpdate();
    void slotMergeUpdate();
    /// ====== 继承实现
    virtual void run()      = 0;
    virtual void slotHelp() = 0;

signals:
    /// ====== 点击对应的操作后发送信号
    void signalCreateArea(const QString &areaName);
    void signalUpdateArea();
    void signalDeleteArea(const QString &areaName);

protected:
    /// ====== 当前项目信息
    ProjectInfo     m_projInfo;
    /// ====== 数据
    AreaDataInfo   *m_AreaDatainfo;
    AreaOption      m_areaOpt;
    UpdateOption    m_updateOpt;
private:
    //基类创建基类的界面
    void createBaseDlg();
    void autoDetectFile(const QString &type);

    QLineEdit   *m_areaNameEdt;
    QLineEdit   *m_RfileEdt,*m_SfileEdt,*m_XfileEdt;

    QLabel       *m_progressHintLbl;
    QProgressBar *m_progressBar;
    QPushButton  *m_operateBtn;
    QCheckBox    *m_autoFileDectCbx;
    QStringList   m_spsFiles;
    bool          first_choose;
    QGroupBox    *m_updateGrpBox;
};
#endif // ABSTRACTAREADIALOG_H
