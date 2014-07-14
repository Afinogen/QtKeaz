#include "treeitem.h"

TreeItem::TreeItem(int _dbId, QString nam, TreeItem *parent)
{
    name = nam;
    parentItem = parent;
    dbId = _dbId;
    qDebug() << parentItem << dbId << name;
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
int TreeItem::getDbId() const
{
    return dbId;
}
