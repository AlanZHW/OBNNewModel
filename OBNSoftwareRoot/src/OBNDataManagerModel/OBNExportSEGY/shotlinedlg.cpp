#include "shotlinedlg.h"


ShotLineDlg::ShotLineDlg(QDialog *parent)
    :QDialog(parent)
{
    this->setWindowTitle(tr("炮线文件"));
    initDlg();
    this->resize(240,360);
}

void ShotLineDlg::setShotLineFiles(const QStringList &fileList)
{
    m_shotLineFiles = fileList;
    listWidget->clear();
    listWidget->addItems(fileList);
}

bool ShotLineDlg::saveShotLineFiles(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
    {
        return false;
    }
    QTextStream out(&file);
    foreach (QString shotFile, m_shotLineFiles)
    {
        out << shotFile << "\n";
    }
    file.close();
    return true;
}

void ShotLineDlg::initDlg()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    listWidget = new QListWidget(this);
    mainLayout->addWidget(listWidget);

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addStretch(1);
    QPushButton *okBtn = new QPushButton(tr("&确定"),this);
    btnLayout->addWidget(okBtn);
    btnLayout->addStretch(1);
    mainLayout->addLayout(btnLayout);
    //
    connect(okBtn,SIGNAL(clicked()),this,SLOT(close()));

    this->setLayout(mainLayout);
}
