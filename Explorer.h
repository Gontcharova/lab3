#ifndef EXPLORER_H
#define EXPLORER_H
#include "FileTableModel.h"
#include "Strategy.h"
#include "IFileCalculateStrategy.h"
#include "ChartModel.h"
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
    explicit Explorer(QWidget *parent = nullptr);
    void updateDataInModel();
    ~Explorer();
protected slots:
    void changeGrouping(int index);
    void changeDisplay(int index);
    void selectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
private:
    Ui::Explorer* ui;

    // стратегии
    IFileCalculateStrategy* current_strategy;
    IFileCalculateStrategy* by_folders;
    IFileCalculateStrategy* by_types;
    // модели
    QFileSystemModel* tree_model;
    FileTableModel* table_model;
    ChartModel* pie_chart;
    ChartModel* bar_chart;

    QString folder_path;
};


#endif // EXPLORER_H
