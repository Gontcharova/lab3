#include "FileTableModel.h"
#include <QLayout>
#include <QLocale>

FileTableModel::FileTableModel(const QList<Data> &data, QObject *parent) : QAbstractTableModel(parent)
{
    m_data = data;
}

FileTableModel::FileTableModel(QLayout *l, QObject *parent) : QAbstractTableModel(parent)
{
    m_view = new QTableView();
    m_view->setModel(this);
    l->addWidget(m_view);
}

int FileTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.count();
}


int FileTableModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return int(ColumnName::PERCENT) + 1;
}

QVariant FileTableModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || m_data.count() <= index.row() || (role != Qt::DisplayRole && role != Qt::EditRole)) {
        return QVariant();
    }
    switch (index.column()) {
    case 0: return m_data[index.row()].m_name;
    case 1:
    {
        QLocale locale(QLocale::English);
        return locale.formattedDataSize(m_data[index.row()].m_size);
    }
    case 2: {
        if (m_data[index.row()].m_ratio < 0)
            return "< 0.01 %";
        else return QString::number(m_data[index.row()].m_ratio, 'f', 2) + " %";
    }
    default: return QVariant();
    }
}

QVariant FileTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }
    if (orientation == Qt::Vertical) {
        return section;
    }
    switch (section) {
    case int(ColumnName::NAME):
        return QString::fromUtf8("Название");
    case int(ColumnName::SIZE):
        return QString::fromUtf8("Размер");
    case int(ColumnName::PERCENT):
        return QString::fromUtf8("В процентах");
    }
    return QVariant();
}

void FileTableModel::setModelData(const QList<Data> &data)
{
    beginResetModel();
    m_data = data;
    endResetModel();
}


void FileTableModel::updateData(const QList<Data> &data)
{
    setModelData(data);
}
