#include "treemodel.h"

TreeModel::TreeModel(QObject *parent): QAbstractItemModel(parent)
{
    root = new TreeItem(0,"Catalog");
}
TreeModel::~TreeModel()
{
    delete root;
}
QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
            return QModelIndex();

        TreeItem *parentItem;

        if (!parent.isValid())
            parentItem = root;
        else
            parentItem = static_cast<TreeItem*>(parent.internalPointer());

        TreeItem *childItem = parentItem->child(row);
        if (childItem) return createIndex(
                    row, column, childItem);
        else return QModelIndex();
}
QModelIndex TreeModel::parent(const QModelIndex &child) const
{
    if (!child.isValid())return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(child.internalPointer());
    TreeItem *parentItem = childItem->parent();

    if (parentItem == root)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}
int TreeModel::rowCount(const QModelIndex &parent = QModelIndex()) const
{
    TreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = root;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}
int TreeModel::columnCount(const QModelIndex &parent = QModelIndex()) const
{
    if(parent.isValid()) return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    return root->columnCount();
}
QVariant TreeModel::data(const QModelIndex &index, int role = Qt::DisplayRole) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    return item->data();
}
void TreeModel::addItem(TreeItem *item)
{
    //item->setParent(root);
    root->appendChild(item);
}
TreeItem *TreeModel::getRoot() const
{
    return root;
}
Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}
