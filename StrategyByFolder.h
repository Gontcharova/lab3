#ifndef STRATEGYBYFOLDER_H
#define STRATEGYBYFOLDER_H
#include "IFileCalculateStrategy.h"

class StrategyByFolder : public IFileCalculateStrategy
{
public:
    StrategyByFolder() = default;
    void calculate(const QString& path) override;
    virtual ~StrategyByFolder() {}
};

#endif // STRATEGYBYFOLDER_H
