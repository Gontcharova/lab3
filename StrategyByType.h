#ifndef STRATEGYBYTYPE_H
#define STRATEGYBYTYPE_H
#include "IFileCalculateStrategy.h"

class StrategyByType : public IFileCalculateStrategy
{
public:
    StrategyByType() {}
    void calculate(const QString &path) override;
    virtual ~StrategyByType() {}
};

#endif // STRATEGYBYTYPE_H
