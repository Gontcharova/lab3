#include "Strategy.h"
#include <QList>

void StrategyContext::setStrategy(IFileCalculateStrategy *strategy)
{
    if (m_strategy) {
        delete m_strategy;
    }
    m_strategy = strategy;
}

QList<Data> StrategyContext::calculate(const QString &path)
{
    if (m_strategy) {
        return m_strategy->calculate(path);
    }
}

StrategyContext::~StrategyContext()
{
    if (m_strategy) {
        delete m_strategy;
    }
}
