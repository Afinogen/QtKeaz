#ifndef TABLEITEM_H
#define TABLEITEM_H

#include <QString>

class TableItem
{
public:
    TableItem();
    TableItem(int id, QString title, QString file);
    int id;
    QString title;
    QString file;
};

#endif // TABLEITEM_H
