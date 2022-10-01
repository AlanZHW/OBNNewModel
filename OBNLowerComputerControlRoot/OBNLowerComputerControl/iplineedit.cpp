#include "iplineedit.h"

//--------------------------------------
IPLineEdit::IPLineEdit(QWidget* pParent)
    : QFrame(pParent)
{
    ip_part1_ = new IpPartLineEdit(this);
    ip_part2_ = new IpPartLineEdit(this);
    ip_part3_ = new IpPartLineEdit(this);
    ip_part4_ = new IpPartLineEdit(this);

    labeldot1_ = new QLabel(this);
    labeldot2_ = new QLabel(this);
    labeldot3_ = new QLabel(this);

    labeldot1_->setText(".");
    labeldot2_->setText(".");
    labeldot3_->setText(".");
    labeldot3_->setMaximumWidth(3);
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->setSpacing(0);
    hLayout->setContentsMargins(0,0,0,0);
    hLayout->addWidget(ip_part1_);
    hLayout->addWidget(labeldot1_);
    hLayout->addWidget(ip_part2_);
    hLayout->addWidget(labeldot2_);
    hLayout->addWidget(ip_part3_);
    hLayout->addWidget(labeldot3_);
    hLayout->addWidget(ip_part4_);

    this->setLayout(hLayout);

    QWidget::setTabOrder(ip_part1_, ip_part2_);
    QWidget::setTabOrder(ip_part2_, ip_part3_);
    QWidget::setTabOrder(ip_part3_, ip_part4_);
    ip_part1_->setNextTabEdit(ip_part2_);
    ip_part2_->setNextTabEdit(ip_part3_);
    ip_part3_->setNextTabEdit(ip_part4_);

    ip_part2_->setPrevTabEdit(ip_part1_);
    ip_part3_->setPrevTabEdit(ip_part2_);
    ip_part4_->setPrevTabEdit(ip_part3_);

    this->setFrameShape(QFrame::Box);
    this->setFrameShadow(QFrame::Sunken);
    QPalette palette  =this->palette();
    palette.setColor(QPalette::Window,Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(palette);

    this->setMaximumHeight(30);

    connect(ip_part1_, SIGNAL(textChanged(const QString&)), this, SLOT(textchangedslot(const QString&)));
    connect(ip_part2_, SIGNAL(textChanged(const QString&)), this, SLOT(textchangedslot(const QString&)));
    connect(ip_part3_, SIGNAL(textChanged(const QString&)), this, SLOT(textchangedslot(const QString&)));
    connect(ip_part4_, SIGNAL(textChanged(const QString&)), this, SLOT(textchangedslot(const QString&)));

    connect(ip_part1_, SIGNAL(textEdited (const QString&)), this, SLOT(texteditedslot(const QString&)));
    connect(ip_part2_, SIGNAL(textEdited (const QString&)), this, SLOT(texteditedslot(const QString&)));
    connect(ip_part3_, SIGNAL(textEdited (const QString&)), this, SLOT(texteditedslot(const QString&)));
    connect(ip_part4_, SIGNAL(textEdited (const QString&)), this, SLOT(texteditedslot(const QString&)));
}

IPLineEdit::~IPLineEdit()
{

}

void IPLineEdit::textchangedslot(const QString& /*text*/)
{
    QString ippart1, ippart2, ippart3, ippart4;
    ippart1 = ip_part1_->text();
    ippart2 = ip_part2_->text();
    ippart3 = ip_part3_->text();
    ippart4 = ip_part4_->text();

    QString ipaddr = QString("%1.%2.%3.%4").arg(ippart1).arg(ippart2).arg(ippart3).arg(ippart4);
    emit textchanged(ipaddr);
}

void IPLineEdit::texteditedslot(const QString &/*text*/)
{
    QString ippart1, ippart2, ippart3, ippart4;
    ippart1 = ip_part1_->text();
    ippart2 = ip_part2_->text();
    ippart3 = ip_part3_->text();
    ippart4 = ip_part4_->text();
    QString ipaddr = QString("%1.%2.%3.%4").arg(ippart1).arg(ippart2).arg(ippart3).arg(ippart4);
    emit textedited(ipaddr);
}

void IPLineEdit::setText(const QString &text)
{
    QString ippart1, ippart2, ippart3, ippart4;
    QString qstring_validate = text;

    // IP地址验证
    QRegExp regexp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
    QRegExpValidator regexp_validator(regexp, this);
    int nPos = 0;
    QValidator::State state = regexp_validator.validate(qstring_validate, nPos);
    // IP合法
    if (state == QValidator::Acceptable)
    {
        QStringList ippartlist = text.split(".");

        int strcount = ippartlist.size();
        int index = 0;
        if (index < strcount)
        {
            ippart1 = ippartlist.at(index);
        }
        if (++index < strcount)
        {
            ippart2 = ippartlist.at(index);
        }
        if (++index < strcount)
        {
            ippart3 = ippartlist.at(index);
        }
        if (++index < strcount)
        {
            ippart4 = ippartlist.at(index);
        }
    }

    ip_part1_->setText(ippart1);
    ip_part2_->setText(ippart2);
    ip_part3_->setText(ippart3);
    ip_part4_->setText(ippart4);
}

QString IPLineEdit::text() const
{
    QString ippart1, ippart2, ippart3, ippart4;
    ippart1 = ip_part1_->text();
    ippart2 = ip_part2_->text();
    ippart3 = ip_part3_->text();
    ippart4 = ip_part4_->text();

    if(ippart1.isEmpty() || ippart2.isEmpty()
            ||ippart3.isEmpty() || ippart4.isEmpty())
        return QString();

    return QString("%1.%2.%3.%4").arg(ippart1).arg(ippart2).arg(ippart3).arg(ippart4);
}

void IPLineEdit::setStyleSheet(const QString &styleSheet)
{
    ip_part1_->setStyleSheet(styleSheet);
    ip_part2_->setStyleSheet(styleSheet);
    ip_part3_->setStyleSheet(styleSheet);
    ip_part4_->setStyleSheet(styleSheet);
}
