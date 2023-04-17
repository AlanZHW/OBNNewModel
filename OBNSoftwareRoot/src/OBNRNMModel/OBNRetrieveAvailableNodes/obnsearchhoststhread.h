#ifndef OBNSEARCHHOSTSTHREAD_H
#define OBNSEARCHHOSTSTHREAD_H

#include <QDebug>
#include <QVector>
#include <QThread>
#include <QString>
#include <QProcess>
#include <QStringList>
#include <QHostAddress>

class OBNSearchHostsThread : public QThread
{
    Q_OBJECT
public:
    explicit OBNSearchHostsThread(QObject *parent = nullptr);
    void     setValue(uint _values, int _row);
protected:
    void run();

signals:
    void signalSearchHostsLinkStatus(int, bool);

private:
    int  m_row;
    uint m_value;
};

#endif // OBNSEARCHHOSTSTHREAD_H
