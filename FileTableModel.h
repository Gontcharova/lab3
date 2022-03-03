#ifndef FILETABLEMODEL_H
#define FILETABLEMODEL_H
#include <QAbstractItemModel>
#include "Data.h"
#include "Observer.h"
#include <QTableView>

class FileTableModel : public QAbstractTableModel, public Observer
{
    Q_OBJECT
private:
    QList<Data> m_data;
    QTableView *m_view;
    enum class ColumnName {
        NAME = 0,
        SIZE,
        PERCENT
    };

public:
    FileTableModel() = default;
    FileTableModel(QLayout* l, QObject *parent = nullptr);
    explicit FileTableModel(const QList<Data>& data, QObject* parent = nullptr);
    void setModelData(const QList<Data>& data);
    ~FileTableModel() {}
    // методы для переопределения
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void updateData(const QList<Data> &data) override;
};
#endif // FILETABLEMODEL_H
