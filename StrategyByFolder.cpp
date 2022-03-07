#include "StrategyByFolder.h"
#include "CommonFunctions.h"
#include <QTextStream>
#include <QDebug>
#include <QFileInfo>
#include <QDir>

void StrategyByFolder::calculate(const QString &path)
{
    QFileInfo folder(path);
    if (!folder.isReadable() || !folder.exists()) {
        qDebug() << "Error! Folder doesn't exist." << Qt::endl;
        return;
    }
    auto foldersAndSizes = FoldersAndSizes(path);
    qint64 total_size = getTotalSizeOfFolder(path);
    auto foldersAndPercents = namesAndPercents(foldersAndSizes, total_size);
    QList<Data> data = AllToData(foldersAndSizes, foldersAndPercents);
    emit OnFinish(data);
//    consoleOutput(foldersAndSizes, foldersAndPercents);
}

void StrategyByFolder::consoleOutput(const QList<QPair<QString, qint64> > &foldersAndSizes, const QList<QPair<QString, double> > &foldersAndPercents) const
{
    QTextStream ts(stdout);
    ts.setCodec("CP866"); // поддержка вывода русских символов в консоль
    auto it1 = foldersAndPercents.begin();
    auto it2 = foldersAndSizes.begin();
    for (; it1 != foldersAndPercents.end(); it1++, it2++ )
    {
        ts << qSetFieldWidth(60) << it1->first << qSetFieldWidth(10)  << it2->second / 1024.0
           << qSetFieldWidth(4)<< "KB";
        if (it1->second < 0) {
            ts << qSetFieldWidth(8) << "< 0.01 %\n";
        } else {
            ts << qSetFieldWidth(8) << QString::number(it1->second, 'f', 2).append(" %") << "\n";
        }
    }
    ts.reset();
}

QList<QPair<QString, qint64> > StrategyByFolder::FoldersAndSizes(const QString& path) const
{
    QFileInfo folder(path);
    QList<QPair<QString, qint64> >  foldersAndSizesList;
    auto absolutePath = folder.absoluteFilePath();
    foldersAndSizesList.append(qMakePair(absolutePath, getDirSize(absolutePath)));
    for (auto& x : QDir(path).entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden, QDir::Name | QDir::Type))
    {
        auto absolutePath = x.absoluteFilePath();
        foldersAndSizesList.append(qMakePair(absolutePath, getTotalSizeOfFolder(absolutePath)));
    }
    return foldersAndSizesList;
}

