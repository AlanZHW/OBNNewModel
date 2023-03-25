#include "mytabpopup.h"

#include <QMouseEvent>
#include <QVBoxLayout>
#include <QDebug>

MyTabPopup::MyTabPopup(QWidget *parent)
    : QDialog(parent)
{
    Qt::WindowFlags windowFlag  = Qt::Dialog;
    windowFlag                  |= Qt::WindowMinimizeButtonHint;
    windowFlag                  |= Qt::WindowMaximizeButtonHint;
    windowFlag                  |= Qt::WindowCloseButtonHint;
    setWindowFlags(windowFlag);
}

void MyTabPopup::setContentWidget(QWidget *page)
{
    if(!page)
    {
        return;
    }
    content=page;
    QVBoxLayout *layout=new QVBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(page);
}

QWidget* MyTabPopup::getContentWidget()
{
    return content;
}

bool MyTabPopup::event(QEvent *event)
{
    switch(event->type())
    {
    case QEvent::MouseButtonRelease:
    case QEvent::NonClientAreaMouseButtonRelease:
    {
        qDebug() << __LINE__ << "\t" << __FUNCTION__;
        QMouseEvent *e=static_cast<QMouseEvent*>(event);
        if(e && e->button()==Qt::LeftButton)
        {
            emit dragRelease(e->globalPos());
        }
    }
    break;
    default:
        break;
    }
    return QDialog::event(event);
}

