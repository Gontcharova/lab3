#ifndef STRATEGYBYTYPE_H
#define STRATEGYBYTYPE_H
#include "IFileCalculateStrategy.h"
#include <QPair>


class StrategyByType : public IFileCalculateStrategy
{
public:
    StrategyByType() {}
    QList<Data> calculate(const QString &path) override;
    virtual ~StrategyByType() {}
    void consoleOutput(const QList<QPair<QString, qint64> >& typesAndSizes,
                       const QList<QPair<QString, double> >& typesAndPercents) const;
protected:
    void TypesAndSizes(const QString& path, QList<QPair<QString, qint64> >& typesAndSizes) const;
    QList<QPair<QString, double> > TypesAndPercents(const QList<QPair<QString, qint64> >& typesAndSizes,
                                                      const qint64& totalSize) const;
    QList<Data> AllToData(const QList<QPair<QString, qint64> >&typesAndSizes, const QList<QPair<QString, double> > &typesAndPercents) const;
};

#endif // STRATEGYBYTYPE_H
