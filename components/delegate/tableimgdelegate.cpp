#include "tableimgdelegate.h"

TableImgDelegate::TableImgDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}
void TableImgDelegate::paint(QPainter *painter,
                       const QStyleOptionViewItem &option,
                       const QModelIndex &index) const
{
    if (!index.data(Qt::DecorationRole).isValid()) return QStyledItemDelegate::paint(painter, option, index);
    else
    {
        QStringList list = index.data(Qt::DecorationRole).toStringList();
        qDebug() << list;
        if (list.size()>0)
        {
            QRect rect = option.rect;

            QPixmap myPixmap(list[1]);
            QApplication::style()->drawItemPixmap(painter,rect,0,myPixmap);
            QApplication::style()->drawItemText(painter,rect,0,QPalette(),true, list[0]);
        }
    }
    return QStyledItemDelegate::paint(painter, option, index);
}

QSize TableImgDelegate::sizeHint(const QStyleOptionViewItem &option,
                           const QModelIndex &index) const
{
    return QStyledItemDelegate::sizeHint(option, index);
}
QWidget *TableImgDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    qDebug()<<index.data();
    /*QLineEdit *l=new QLineEdit();
    l->setText("sdf");
    return l;*/
}
void TableImgDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    qDebug()<<index.data();
    /*QLineEdit * edit = (QLineEdit *)editor;
    QString value = edit->text();
    model->setData(index, value, Qt::EditRole);*/
}
