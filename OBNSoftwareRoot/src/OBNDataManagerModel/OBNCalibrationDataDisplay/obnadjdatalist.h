#ifndef OBNADJDATALIST_H
#define OBNADJDATALIST_H

#include <QDebug>
#include <QLabel>
#include <QDialog>

#include "obncalibrationdatapublic.h"

namespace Ui {
class OBNADJDataList;
}

class OBNADJDataList : public QDialog
{
    Q_OBJECT

public:
    explicit OBNADJDataList(QWidget *parent = nullptr);
    ~OBNADJDataList();
    /// ====== 设置当前显示的数据
    void setCurrentDataVector(const QList<ADJDispInform>&, const QList<ADJDispInform>&, const QList<ADJDispInform>&);
private:
    Ui::OBNADJDataList *ui;
};

#endif // OBNADJDATALIST_H
