#ifndef STRATEGY_H
#define STRATEGY_H
#include "IFileCalculateStrategy.h"

class StrategyContext
{
    IFileCalculateStrategy* m_strategy = nullptr;
public:
    StrategyContext(IFileCalculateStrategy* strategy) : m_strategy(strategy) {}

    void setStrategy(IFileCalculateStrategy* strategy);
    void calculate(const QString& path);

    ~StrategyContext();
};


#endif // STRATEGY_H
