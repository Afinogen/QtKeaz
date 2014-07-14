#ifndef TREEITEM_H
#define TREEITEM_H

#include <QString>
#include <QList>
#include <QVariant>
#include <QDebug>

class TreeItem
{
public:
    TreeItem(int dbId, QString name, TreeItem *parent = 0);
    ~TreeItem();
    void appendChild(TreeItem *cont);
    TreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data() const;
    int getDbId() const;
    int row() const;
    TreeItem *parent();
    void setParent(TreeItem *parent);
private:
    QList<TreeItem*> childItems;
    QString name;
    TreeItem *parentItem;
    int dbId;
};

#endif // TREEITEM_H
