#include "tablemodelstring.h"

TableModelString::TableModelString(QObject *parent) :
    QAbstractTableModel(parent)
{
        headData.push_back("Наименование");
        headData.push_back("Артикул");
}
int TableModelString::rowCount(const QModelIndex &parent) const
{
    return listData.size()/columnCount();
}
int TableModelString::columnCount(const QModelIndex &parent) const
{
    return 2;//5;
}
QVariant TableModelString::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant::Invalid;
    if (role == Qt::DisplayRole)
    {
    int pos = this->columnCount()*index.row()+index.column();
    qDebug()<<"pos: "<<pos;
    if (pos>listData.size()) return QVariant::Invalid;
    TableStringItem *item=listData[pos];

    if (index.column()==0) return item->name;
    else if (index.column()==1) return item->articul;
    else return QVariant::Invalid;
    }
    return QVariant::Invalid;

}
Qt::ItemFlags TableModelString::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}
QVariant TableModelString::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
               return QVariant();
       if(orientation == Qt::Horizontal && role == Qt::DisplayRole){
           return headData.at(section); // заголовки столбцов
       }else{
           //return QString("%1").arg( section + 1 ); // возвращаем номера строк
       }
}
void TableModelString::addItem(QString name, QString articul)
{
    TableStringItem *item=new TableStringItem();
    item->name=name;
    item->articul=articul;
    listData.push_back(item);
}
