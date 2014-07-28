#include "tablemodel.h"

TableModel::TableModel(QObject *parent) :
    QAbstractTableModel(parent)
{

}
int TableModel::rowCount(const QModelIndex &parent) const
{
    if (listData.isEmpty()) return 0;
    if (listData.size()/columnCount()==0) return 1;
    else return listData.size()/columnCount();
}
int TableModel::columnCount(const QModelIndex &parent) const
{
    if (listData.isEmpty()) return 0;
    if (listData.size()<3) return listData.size();
    else return 3;
}
QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();
    if (role == Qt::DecorationRole)
    {
            qDebug()<<"Array pos:"<<this->columnCount()*index.row()+index.column();
            TableItem *item=listData[this->columnCount()*index.row()+index.column()];
            QStringList ret;
            ret.push_back(item->title);
            ret.push_back(item->file);
            qDebug() << QVariant(ret);
            return QVariant(ret);
    }

    return QVariant(0,0);
}
Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    //Qt::ItemFlags flags = QAbstractTableModel::flags(index);
        /*if (index.isValid() && (index.column() == 0))
            flags = flags & Qt::DecorationRole;*/
       // return index.isValid() ? (flags & ~Qt::ItemIsEditable) : flags;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void TableModel::addItem(int id, QString title, QString file)
{
    TableItem *item=new TableItem(id,title,file);
    listData.push_back(item);
}
void TableModel::clearModel()
{
    listData.clear();
    //for(int i=0;i<list)
}
TableItem *TableModel::getItem(int pos) const
{
    if (pos<0 || pos>listData.size()) return NULL;
    return listData[pos];
}
