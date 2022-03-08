#include "Explorer.h"
#include "ui_explorer.h"
#include "StrategyByFolder.h"
#include "StrategyByType.h"

Explorer::Explorer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Explorer)
{
    ui->setupUi(this);
    tree_model = new QFileSystemModel(this);
    by_folders = new StrategyByFolder();
    by_types = new StrategyByType();
    current_strategy = by_folders;
    tree_model->setRootPath(QDir::currentPath());
    tree_model->setFilter(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Hidden);
    ui->treeView->setModel(tree_model);
    ui->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

    table_model = new FileTableModel(ui->stackedWidget->layout());
    pie_chart = new PieChart(ui->stackedWidget->layout());
    bar_chart = new BarChart(ui->stackedWidget->layout());

    connect(by_folders, &IFileCalculateStrategy::OnFinish, table_model, &FileTableModel::updateData);
    connect(by_folders, &IFileCalculateStrategy::OnFinish, pie_chart, &ChartModel::updateData);
    connect(by_folders, &IFileCalculateStrategy::OnFinish, bar_chart, &ChartModel::updateData);

    connect(by_types, &IFileCalculateStrategy::OnFinish, table_model, &FileTableModel::updateData);
    connect(by_types, &IFileCalculateStrategy::OnFinish, pie_chart, &ChartModel::updateData);
    connect(by_types, &IFileCalculateStrategy::OnFinish, bar_chart, &ChartModel::updateData);

    connect(ui->displayBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Explorer::changeDisplay);
    connect(ui->groupBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Explorer::changeGrouping);
    connect(ui->treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this,  &Explorer::selectionChanged);
}


Explorer::~Explorer()
{
    delete ui;
    delete tree_model;
    delete table_model;
    delete pie_chart;
    delete bar_chart;
    delete by_folders;
    delete by_types;
}

void Explorer::changeGrouping(int index)
{
    switch (index) {
        case 0:
            current_strategy = by_folders;
            break;
        case 1:
            current_strategy = by_types;
            break;
        default:
            current_strategy = by_folders;
            break;
    }
    current_strategy->calculate(folder_path);
}

void Explorer::changeDisplay(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}

void Explorer::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected);

    QModelIndexList indexes = selected.indexes();
    folder_path = tree_model->filePath(indexes[0]);
    current_strategy->calculate(folder_path);
}
