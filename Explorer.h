#ifndef EXPLORER_H
#define EXPLORER_H
#include "FileTableModel.h"
#include "Strategy.h"
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
    void updateDataInModel();
    ~Explorer();
protected slots:
    void changeGrouping(int index);
    void selectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
private:
    Ui::Explorer* ui;
    QFileSystemModel* tree_model;
    FileTableModel* table_model;
    QList<Data> data;
    StrategyContext* context;
    QString folder_path;
    GroupedBy grouping;
};


#endif // EXPLORER_H
