#ifndef IPPARTLINEEDIT_H
#define IPPARTLINEEDIT_H

#include <QDebug>
#include <QKeyEvent>
#include <QLineEdit>
#include <QIntValidator>

class IpPartLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    IpPartLineEdit(QWidget *parent = 0);
    ~IpPartLineEdit(void);

    void setNextTabEdit(QLineEdit *nexttab) { next_tab_ = nexttab; }
    void setPrevTabEdit(QLineEdit *prevtab) { prev_tab_ = prevtab; }

protected:
    void focusInEvent(QFocusEvent *e);
    void keyPressEvent(QKeyEvent *event);

private slots:
    void  text_edited(const QString& text);

private:
    QLineEdit  *next_tab_;
    QLineEdit  *prev_tab_;
};


#endif // IPPARTLINEEDIT_H
