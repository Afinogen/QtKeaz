#include "treeitem.h"

TreeItem::TreeItem(QString nam, TreeItem *parent)
{
    name = nam;
    parentItem = parent;

    qDebug() << parentItem << name;
}
TreeItem::~TreeItem()
{
    qDeleteAll(childItems);
}
void TreeItem::appendChild(TreeItem *cont)
{
    childItems.append(cont);
}

TreeItem* TreeItem::child(int row)
{
    return childItems.value(row);
}

int TreeItem::childCount() const
{
    return childItems.size();
}

int TreeItem::columnCount() const
{
    return 1;
}

QVariant TreeItem::data() const
{
    //qDebug()<<"1: "<< name;
    return name;
}

TreeItem* TreeItem::parent()
{
    return parentItem;
}

int TreeItem::row() const
{
    qDebug() << parentItem;
    if(parentItem)
    {
        return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));
    }
    return 0;
}
void TreeItem::setParent(TreeItem *parent)
{
    parentItem = parent;
}
