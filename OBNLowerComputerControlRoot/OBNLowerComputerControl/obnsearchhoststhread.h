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

    void setValues(const QVector<uint>& pValues)
    {
        m_values = pValues;
    }
    void setValue(const uint& pValue)
    {
        m_values.append(pValue);
    }

protected:
    void run();

signals:
    void signalSearchHostsLinkStatus(const QString&, const int&, bool);

private:
    QVector<uint> m_values;
};

#endif // OBNSEARCHHOSTSTHREAD_H
