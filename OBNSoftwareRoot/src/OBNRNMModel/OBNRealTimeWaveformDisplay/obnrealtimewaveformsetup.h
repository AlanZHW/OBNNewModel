#ifndef OBNREALTIMEWAVEFORMSETUP_H
#define OBNREALTIMEWAVEFORMSETUP_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QMessageBox>

#include "obnrealtimewaveformpublic.h"

namespace Ui {
class OBNRealTimeWaveformSetup;
}

class OBNRealTimeWaveformSetup : public QDialog
{
    Q_OBJECT

public:
    explicit OBNRealTimeWaveformSetup(QWidget *parent = nullptr);
    ~OBNRealTimeWaveformSetup();
    void setCurrentHostInform(const QStringList&);

signals:
    void signalCurrentTcpInformList(const QList<TCPInform>&);

private:
    QStringList m_BaudRateInformList;

    Ui::OBNRealTimeWaveformSetup *ui;
};

#endif // OBNREALTIMEWAVEFORMSETUP_H
