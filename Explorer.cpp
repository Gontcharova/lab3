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
    table_model = new FileTableModel;
    context = new StrategyContext;
    tree_model->setRootPath(QDir::currentPath());
    tree_model->setFilter(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Hidden);
    ui->treeView->setModel(tree_model);
    ui->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    grouping = GroupedBy::Folders;

    connect(ui->groupBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Explorer::changeGrouping);
    connect(ui->treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this,  &Explorer::selectionChanged);
}

void Explorer::updateDataInModel()
{
    if (folder_path.isEmpty())
        return;
    switch (grouping) {
    case GroupedBy::Folders:
        context->setStrategy(new StrategyByFolder);
        break;
    case GroupedBy::Types:
        context->setStrategy(new StrategyByType);
        break;
    }
    data = context->calculate(folder_path);
    if(data.isEmpty())
        return;
    table_model->setModelData(data);
    ui->tableView->setModel(table_model);
}

Explorer::~Explorer()
{
    delete ui;
    delete tree_model;
    delete table_model;
    delete context;
}

void Explorer::changeGrouping(int index)
{
    switch (index) {
        case 0:
            grouping = GroupedBy::Folders;
            break;
        case 1:
            grouping = GroupedBy::Types;
            break;
        default:
            grouping = GroupedBy::Folders;
            break;
    }
    updateDataInModel();
}

void Explorer::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected);

    QModelIndexList indexes = selected.indexes();
    folder_path = tree_model->filePath(indexes[0]);
    updateDataInModel();
}
