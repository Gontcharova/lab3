#ifndef IFILECALCULATESTRATEGY_H
#define IFILECALCULATESTRATEGY_H
#include "Data.h"
#include <QString>
#include <QList>
#include "Observer.h"
/*
    IFileCalculateStrategy - интерфейс всех стратегий.
    calculate - чистый виртуальный метод. Через этот метод происходит выполнение алгоритма соответсвующей стратегии.
*/

class IFileCalculateStrategy
{
private:
    QList<Observer* > observers;
public:
    IFileCalculateStrategy() = default;
    void subscribeToEvent(Observer* observer)
    {
        if (observer)
            observers.push_back(observer);
    }
    void unsubscribe(Observer* observer)
    {
        if (observer)
            observers.removeOne(observer);
    }
    void onFinish(const QList<Data>& data)
    {
        for (auto& obs : observers)
            obs->updateData(data);
    }
    virtual void calculate(const QString& path) = 0;
    virtual ~IFileCalculateStrategy() {}
};

#endif // IFILECALCULATESTRATEGY_H
