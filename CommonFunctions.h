#ifndef COMMONFUNCTIONS_H
#define COMMONFUNCTIONS_H
#include <QString>
#include <QDir>
#include <QList>
#include <QPair>


inline qint64 getTotalSizeOfFolder(const QString& path)
{
    QDir folder(path);
    qint64 totalSize = 0;
    for (auto& it : folder.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden, QDir::Name | QDir::Type | QDir::Size))
    {
        if (it.isDir() && !it.isSymLink()) {
            totalSize += getTotalSizeOfFolder(it.absoluteFilePath());
        } else {
            totalSize += it.size();
        }
    }
    return totalSize;
}

inline qint64 sumSizes(const QList<QPair<QString, qint64>>& ListOfSizes)
{
    qint64 totalSize = 0;
    for (auto& x : ListOfSizes) {
        totalSize += x.second;
    }
    return totalSize;
}

inline qint64 getDirSize(const QString& path)
{
    qint64 totalSize = 0;
    QDir folder(path);
    for (auto& it : folder.entryInfoList(QDir::Files | QDir::NoDotAndDotDot , QDir::Name | QDir::Type))
        totalSize += it.size();
    return totalSize;
}


#endif // COMMONFUNCTIONS_H
