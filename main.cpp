#include <QApplication>
#include "Explorer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Explorer exp;
    exp.show();
    return a.exec();
}
