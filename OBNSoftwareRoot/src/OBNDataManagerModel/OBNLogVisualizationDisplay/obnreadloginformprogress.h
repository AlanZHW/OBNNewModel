#ifndef OBNREADLOGINFORMPROGRESS_H
#define OBNREADLOGINFORMPROGRESS_H

#include <QDialog>

namespace Ui {
class OBNReadLogInformProgress;
}

class OBNReadLogInformProgress : public QDialog
{
    Q_OBJECT

public:
    explicit OBNReadLogInformProgress(QWidget *parent = nullptr);
    ~OBNReadLogInformProgress();

    void setValue(const int&);
    void setRange(const int&, const int&);

signals:
    void signalCancenReadLogThread();

private:
    Ui::OBNReadLogInformProgress *ui;
};

#endif // OBNREADLOGINFORMPROGRESS_H
