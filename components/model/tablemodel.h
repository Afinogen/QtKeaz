#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QPixmap>
#include <QImage>
#include <QPainter>
#include <QDebug>
#include "components/model/tableitem.h"

class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TableModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    void addItem(int id, QString title, QString file);
    void clearModel();
    TableItem *getItem(int pos) const;
private:
    QList<TableItem*> listData;
signals:

public slots:

};

#endif // TABLEMODEL_H
