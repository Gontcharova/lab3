#ifndef STRATEGYBYFOLDER_H
#define STRATEGYBYFOLDER_H
#include "IFileCalculateStrategy.h"
#include "Data.h"
#include <QPair>
#include <QList>

class StrategyByFolder : public IFileCalculateStrategy
{
public:
    StrategyByFolder() = default;
    void calculate(const QString& path) override;
    virtual ~StrategyByFolder() {}
    void consoleOutput(const QList<QPair<QString, qint64> >& foldersAndSizes,
                       const QList<QPair<QString, double> >& foldersAndPercents) const;
protected:
    QList<QPair<QString, qint64> > FoldersAndSizes(const QString& path) const;
};

#endif // STRATEGYBYFOLDER_H
