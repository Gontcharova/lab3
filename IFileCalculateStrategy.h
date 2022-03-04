#ifndef IFILECALCULATESTRATEGY_H
#define IFILECALCULATESTRATEGY_H
#include "Data.h"
#include <QString>
/*
    IFileCalculateStrategy - интерфейс всех стратегий.
    calculate - чистый виртуальный метод. Через этот метод происходит выполнение алгоритма соответсвующей стратегии.
*/

class IFileCalculateStrategy
{
public:
    IFileCalculateStrategy() = default;

    virtual QList<Data> calculate(const QString& path) = 0;
    virtual ~IFileCalculateStrategy() {}
};

#endif // IFILECALCULATESTRATEGY_H
