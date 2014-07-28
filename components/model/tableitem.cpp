#include "tableitem.h"

TableItem::TableItem()
{
}
TableItem::TableItem(int id, QString title, QString file)
{
    this->id=id;
    this->title=title;
    this->file=file;
}
