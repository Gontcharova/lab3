#include "Explorer.h"
#include "ui_explorer.h"


Explorer::Explorer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Explorer)
{
    ui->setupUi(this);
    tree_model = new QFileSystemModel(this);
    table_model = new FileTableModel;
    tree_model->setRootPath(QDir::currentPath());
    tree_model->setFilter(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Hidden);
    ui->treeView->setModel(tree_model);
    ui->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    grouping = GroupedBy::Folders;
}

Explorer::~Explorer()
{
    delete ui;
    delete tree_model;
    delete table_model;
}
