#ifndef SHOTLINEDLG_H
#define SHOTLINEDLG_H

#include <QDialog>
#include <QDebug>
#include <QListWidget>
#include <QMainWindow>
#include <QHBoxLayout>

#include "projectarea.h"
#include "publicwidgets.h"

class ShotLineDlg : public QDialog
{
    Q_OBJECT
public:
    ShotLineDlg(QDialog *parent = 0);
    void setShotLineFiles(const QStringList &fileList);
    bool saveShotLineFiles(const QString &fileName); //保存
    QStringList shotLineFiles() const{return m_shotLineFiles;}
private:
    void         initDlg();
    QListWidget *listWidget;
    QStringList  m_shotLineFiles;
};

#endif // SHOTLINEDLG_H
