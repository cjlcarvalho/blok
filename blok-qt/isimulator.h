#ifndef ISIMULATOR_H
#define ISIMULATOR_H

#include <QObject>
#include <QList>
#include <QPointF>

class ISimulator : public QObject
{
    Q_OBJECT

Q_SIGNALS:
    void bodiesUpdated(const QList<QPointF> &bodies);
    void bodiesCreated(const QList<QPointF> &bodies);
    void youWon();
    void youLost();

public Q_SLOTS:
    virtual void init() = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void removeBody(const QPointF &body) = 0;

protected:
    explicit ISimulator(QObject *parent = 0);

protected:
    QList<QPointF> m_bodiesPoints;
};

#endif // ISIMULATOR_H
