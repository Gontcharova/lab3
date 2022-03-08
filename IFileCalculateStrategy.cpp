#include "IFileCalculateStrategy.h"


QList<Data> IFileCalculateStrategy::AllToData(const QList<QPair<QString, qint64> > &nameAndSizes,
                                              const QList<QPair<QString, double> > &nameAndPercents) const
{
    QList<Data> data;
    auto it1 = nameAndPercents.begin();
    auto it2 = nameAndSizes.begin();
    for (; it1 != nameAndPercents.end(); it1++, it2++ )
    {
        data.push_back(Data(it1->first, it2->second, it1->second));
    }
    return data;
}

QList<QPair<QString, double> > IFileCalculateStrategy::namesAndPercents(const QList<QPair<QString, qint64> > &namesAndSizes, const qint64 &totalSize) const
{
    QList<QPair<QString, double> > namesListPercentage;
    double percent;
    for (auto& x : namesAndSizes) {
        if (totalSize != 0) {
            percent = double(x.second * 100) / totalSize;
            if (percent < 0.01 && percent != 0)
                percent = -percent; // метка для папок меньше 0.01 процента
        } else {
            percent = 0;
        }
        namesListPercentage.append(qMakePair(x.first, percent));
    }
    return namesListPercentage;
}
