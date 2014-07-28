#ifndef TABLESTRINGITEM_H
#define TABLESTRINGITEM_H

#include <QObject>

class TableStringItem : public QObject
{
    Q_OBJECT
public:
    explicit TableStringItem(QObject *parent = 0);
    QString name;
    QString articul;
signals:

public slots:

};

#endif // TABLESTRINGITEM_H
