#ifndef FILEDETAILDLG_H
#define FILEDETAILDLG_H

#include <QDialog>
#include <QMainWindow>
#include <QDebug>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QTextBrowser>
#include <QTableWidget>

#include "projectarea.h"
#include "publicwidgets.h"
#include "core.h"
//#include "qcplotter.h"

class  FileDetailDlg : public QDialog
{
    Q_OBJECT
public:
    FileDetailDlg(QWidget *parent = 0);
    void setSegyFileInfo(char *textHeader,BinaryHead *headers,SegyInfo *segyInfo);
private:
    void initDlg();
    void getBinaryHeaderInfos(QStringList &fieldAndDesc);
private:
    QTextBrowser   *m_txtHeaderBrser;
    QTableWidget   *m_binHeaderTab;
};

#endif // FILEDETAILDLG_H
