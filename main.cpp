#include <QCoreApplication>
#include "Strategy.h"
#include "StrategyByFolder.h"
#include "StrategyByType.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    StrategyContext* ctx = new StrategyContext(new StrategyByType);
    ctx->calculate("D:/temp_folder");
    ctx->setStrategy(new StrategyByFolder);
    ctx->calculate("D:/temp_folder");
    delete ctx;
    return 0;
}
