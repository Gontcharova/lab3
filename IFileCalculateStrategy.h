#ifndef IFILECALCULATESTRATEGY_H
#define IFILECALCULATESTRATEGY_H
#include "Data.h"
#include <QString>
#include <QList>
#include <QObject>
/*
    IFileCalculateStrategy - интерфейс всех стратегий.
    calculate - чистый виртуальный метод. Через этот метод происходит выполнение алгоритма соответсвующей стратегии.
*/

class IFileCalculateStrategy :  public QObject
{
    Q_OBJECT
signals:
    void OnFinish(const QList<Data>& data);
public:
    IFileCalculateStrategy(QObject* parent = nullptr)  : QObject(parent) {}
    virtual void calculate(const QString& path) = 0;

    virtual ~IFileCalculateStrategy() {}
protected:
    QList<Data> AllToData(const QList<QPair<QString, qint64> >&nameAndSizes,
                          const QList<QPair<QString, double> > &nameAndPercents) const;
    QList<QPair<QString, double> > namesAndPercents(const QList<QPair<QString, qint64> >& namesAndSizes,
                                                      const qint64& totalSize) const;
};

#endif // IFILECALCULATESTRATEGY_H
