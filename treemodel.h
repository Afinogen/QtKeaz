#ifndef TREEMODEL_H
#define TREEMODEL_H
#include <QAbstractItemModel>
#include <treeitem.h>

class TreeModel: public QAbstractItemModel
{
    //Q_OBJECT
public:
    TreeModel(QObject *parent = 0);
    ~TreeModel();
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    void addItem(TreeItem *item);
    TreeItem *getRoot() const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
private:
    TreeItem *root;
};

#endif // TREEMODEL_H
