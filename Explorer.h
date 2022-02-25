#ifndef EXPLORER_H
#define EXPLORER_H
#include "FileTableModel.h"
#include <QWidget>
#include <QItemSelection>
#include <QFileSystemModel>

namespace Ui {
    class Explorer;
}


class Explorer : public QWidget
{
    Q_OBJECT
public:
    enum class GroupedBy {
        Folders,
        Types
    };
    explicit Explorer(QWidget *parent = nullptr);
    ~Explorer();
private:
    Ui::Explorer* ui;
    QFileSystemModel* tree_model;
    FileTableModel* table_model;
    QList<Data> data;
    GroupedBy grouping;
};


#endif // EXPLORER_H
