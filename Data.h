#ifndef DATA_H
#define DATA_H
#include <QString>

struct Data
{
    QString m_name;
    qint64 m_size;
    qreal m_ratio;
    Data(const QString& name, qint64 size, qreal ratio)
                : m_name(name), m_size(size), m_ratio(ratio) {}
};
#endif // DATA_H
