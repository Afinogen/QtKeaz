#ifndef TABLEMODELSTRING_H
#define TABLEMODELSTRING_H

#include <QAbstractTableModel>
#include <QList>
#include <QString>
#include <QDebug>
#include <QVariant>
#include "components/model/tablestringitem.h"

class TableModelString : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TableModelString(QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    void addItem(QString name, QString articul);
private:
    QList<TableStringItem*> listData;
    QStringList headData;
signals:

public slots:

};

#endif // TABLEMODELSTRING_H
