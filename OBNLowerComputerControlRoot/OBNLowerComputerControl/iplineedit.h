#ifndef IPLINEEDIT_H
#define IPLINEEDIT_H

#include <QLabel>
#include <QWidget>
#include <QFrame>
#include <QObject>
#include <QString>
#include <QHBoxLayout>
#include <QRegExpValidator>

#include "ippartlineedit.h"

#include <QtUiPlugin/QDesignerCustomWidgetCollectionInterface>

class IPLineEdit : public QFrame
{
    Q_OBJECT
public:
    IPLineEdit(QWidget* parent = 0);

    ~IPLineEdit();

    void setText(const QString &text);

    //IP地址不合法则返回空
    QString text() const;

    void setStyleSheet(const QString &styleSheet);

signals:
    void textchanged(const QString& text);
    void textedited(const QString &text);

private slots:
    void textchangedslot(const QString& text);
    void texteditedslot(const QString &text);

private:
    IpPartLineEdit *ip_part1_;
    IpPartLineEdit *ip_part2_;
    IpPartLineEdit *ip_part3_;
    IpPartLineEdit *ip_part4_;

    QLabel *labeldot1_;
    QLabel *labeldot2_;
    QLabel *labeldot3_;
};

#endif // IPLINEEDIT_H
