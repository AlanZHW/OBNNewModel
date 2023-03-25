#ifndef OPENSEGYDLG_H
#define OPENSEGYDLG_H

#include <QDebug>
#include <QLineEdit>
#include <QFileDialog>
#include <QMessageBox>
#include <QButtonGroup>

#include "projectarea.h"
#include "publicwidgets.h"
#include "core.h"
#include "filedetaildlg.h"
#include "publicHostInform.h"
#include "segy.h"
#include "opensegydlg_global.h"

namespace Ui {
class OpenSegyDlg;
}
class OPENSEGYDLG_EXPORT OpenSegyDlg : public QDialog
{
    Q_OBJECT
public:
    OpenSegyDlg(QWidget *parent = 0);
    ~OpenSegyDlg();

    int maxShowTraces() const {return m_maxShowTraces;}
    int components()const{return m_OpenFilesType;}
    int startTrace() const {return m_startTrace;}
signals:
    void signalOpenedFile(QList<SegyFileHandle*>, int, int, OpenFilesType);

private slots:
    void on_okBtn_clicked();

    void on_cancelBtn_clicked();

    void on_detailBtn_clicked();

    void on_OneComRbtn_clicked();

    void on_FourComRbtn_clicked();

    void slotBrwBtnClicked(int id);

private:
    bool openSegyFile(const QStringList &fileName);
    bool getFileList(QStringList &fileList);

private:
    Ui::OpenSegyDlg  *ui;
    OpenFilesType     m_OpenFilesType;
    QList<QLineEdit *>m_fileNameEdits;
    QList<SegyFileHandle *> m_segyFileHandles;
    /// ====== 文件句柄
    int               m_maxShowTraces;
    int               m_startTrace;
    FileDetailDlg    *m_fileDetailDlg;
    QButtonGroup     *m_brwserBtnGrp;
    QString           m_currentPath; //保存当前数据文件目录，方便下次选择文件
};

#endif // OPENSEGYDLG_H
