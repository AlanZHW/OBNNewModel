#include "mytabbar.h"

MyTabBar::MyTabBar(QWidget *parent)
    : QTabBar(parent)
{
    setAttribute(Qt::WA_StyledBackground);
    /// ====== tab页签可以拖拽交换位置
    setMovable(true);
    /// ====== tab页签显示关闭按钮
    setTabsClosable(true);
}

void MyTabBar::mousePressEvent(QMouseEvent *event)
{
    QTabBar::mousePressEvent(event);
    if(event->button() == Qt::LeftButton)
    {
        theDragPress = true;
    }
}

void MyTabBar::mouseMoveEvent(QMouseEvent *event)
{
    QTabBar::mouseMoveEvent(event);
    if(theDragPress && event->buttons())
    {
        if(!theDragOut && !contentsRect().contains(event->pos()))
        {
            theDragOut = true;
            emit beginDragOut(this->currentIndex());

            QMouseEvent *e=new QMouseEvent(QEvent::MouseButtonRelease,
                                           this->mapFromGlobal(QCursor::pos()),
                                           Qt::LeftButton,
                                           Qt::LeftButton,
                                           Qt::NoModifier);
            QApplication::postEvent(this,e);
        }
    }
}

void MyTabBar::mouseReleaseEvent(QMouseEvent *event)
{
    QTabBar::mouseReleaseEvent(event);
    theDragPress=false;
    theDragOut  =false;
}
