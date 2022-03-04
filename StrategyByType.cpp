#include "StrategyByType.h"
#include "CommonFunctions.h"
#include <QFileInfo>
#include <QDir>
#include <QDebug>
#include <QTextStream>

QList<Data> StrategyByType::calculate(const QString &path)
{
    QFileInfo folder(path);
    if (!folder.isReadable() || !folder.exists()) {
        qDebug() << "Error! Folder doesn't exist." << Qt::endl;
        return QList<Data>();
    }
    QList<QPair<QString, qint64> > typesAndSizes;
    TypesAndSizes(path, typesAndSizes);
    qint64 total_size = getTotalSizeOfFolder(path);
    auto typesAndPercents = TypesAndPercents(typesAndSizes, total_size);
//    consoleOutput(typesAndSizes, typesAndPercents);
    return AllToData(typesAndSizes, typesAndPercents);
}


void StrategyByType::TypesAndSizes(const QString &path, QList<QPair<QString, qint64> > &typesAndSizes) const
{
    for (auto& x : QDir(path).entryInfoList(QDir::Dirs | QDir::Files | QDir::Hidden | QDir::NoDotAndDotDot, QDir::Name | QDir::Type))
    {
        if (x.isDir())
            TypesAndSizes(x.absoluteFilePath(), typesAndSizes);
        else
        {
            bool found = false;
            for (int i = 0; i < typesAndSizes.size(); i++) {
                if (typesAndSizes[i].first == x.suffix().toLower()) {
                    typesAndSizes[i].second += x.size();
                    found = true;
                }
            }
            if (!found)
                typesAndSizes.append(qMakePair(x.suffix().toLower(), x.size()));
        }
    }
}

QList<QPair<QString, double> > StrategyByType::TypesAndPercents(const QList<QPair<QString, qint64> > &typesAndSizes, const qint64 &totalSize) const
{
    double total_percent;
    QList<QPair<QString, double> > TypesAndPercents;
    for (auto& x : typesAndSizes) {
        if (totalSize != 0) {
            total_percent = double(x.second * 100) / totalSize;
            if (total_percent < 0.01 && total_percent != 0)
                total_percent = -total_percent; // метка для папок меньше 0.01 процента
        } else {
            total_percent = 0;
        }
        TypesAndPercents.append(qMakePair(x.first, total_percent));
    }
    return TypesAndPercents;
}

QList<Data> StrategyByType::AllToData(const QList<QPair<QString, qint64> > &typesAndSizes, const QList<QPair<QString, double> > &typesAndPercents) const
{
    QList<Data> data;
    auto it1 = typesAndPercents.begin();
    auto it2 = typesAndSizes.begin();
    for (; it1 != typesAndPercents.end(); it1++, it2++ )
    {
        data.push_back(Data(it1->first, it2->second, it1->second));
    }

    return data;
}

void StrategyByType::consoleOutput(const QList<QPair<QString, qint64> > &typesAndSizes, const QList<QPair<QString, double> > &typesAndPercents) const
{
    QTextStream ts(stdout);
    ts.setCodec("CP866"); // поддержка вывода русских символов в консоль
    ts.setRealNumberNotation(QTextStream::FixedNotation);
    ts.setRealNumberPrecision(2);
    auto it1 = typesAndPercents.begin();
    auto it2 = typesAndSizes.begin();
    for (; it1 != typesAndPercents.end(); it1++, it2++ )
    {
        ts << qSetFieldWidth(20) << it1->first << qSetFieldWidth(10)  << it2->second / 1024.0
           << qSetFieldWidth(4)<< "KB";
        if (it1->second < 0) {
            ts << qSetFieldWidth(8) << "< 0.01 %\n";
        } else {
            ts << qSetFieldWidth(8) << QString::number(it1->second, 'f', 2).append(" %") << "\n";
        }
    }
    ts.reset();
}
