#ifndef FILETABLEMODEL_H
#define FILETABLEMODEL_H
#include <QAbstractItemModel>
#include "Data.h"

class FileTableModel : public QAbstractTableModel
{
    Q_OBJECT
private:
    QList<Data> m_data;
    enum class ColumnName {
        NAME = 0,
        SIZE,
        PERCENT
    };

public:
    FileTableModel() = default;
    explicit FileTableModel(const QList<Data>& data, QObject* parent = nullptr);
    void setModelData(const QList<Data>& data);
    ~FileTableModel() {}
    // методы для переопределения
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

};
#endif // FILETABLEMODEL_H
