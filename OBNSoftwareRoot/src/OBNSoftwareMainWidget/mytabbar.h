#ifndef MYTABBAR_H
#define MYTABBAR_H

#include <QDebug>
#include <QTabBar>
#include <QApplication>
#include <QMouseEvent>

class MyTabBar : public QTabBar
{
    Q_OBJECT
public:
    explicit MyTabBar(QWidget *parent = nullptr);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    //拖出时发出信号
    void beginDragOut(int index);

private:
    bool theDragPress= false;
    bool theDragOut  = false;
};

#endif // MYTABBAR_H
