#ifndef TABLEIMGDELEGATE_H
#define TABLEIMGDELEGATE_H

#include <QAbstractItemDelegate>
#include <QStyledItemDelegate>
#include <QLabel>
#include <QLineEdit>
#include <QPainter>
#include <QApplication>
#include <QDebug>


class TableImgDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit TableImgDelegate(QObject *parent = 0);
    void paint(QPainter *painter,
                           const QStyleOptionViewItem &option,
                           const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option,
                               const QModelIndex &index) const;
    void setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const;
    QWidget *createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const;
signals:

public slots:

};

#endif // TABLEIMGDELEGATE_H
