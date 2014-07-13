#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QFileInfo>
#include <QStandardPaths>
#include "treeitem.h"
#include "treemodel.h"
#include "downloadmanager.h"


class MainController: public QObject
{
    Q_OBJECT
public:
    MainController(QObject *parent=0);
    ~MainController();
    void connectDB();
    bool isConnectedDB();
    void closeDB();
    TreeModel *createTreeView();
public slots:
    void conDB();
private:
    void createTreeItem(TreeItem *parentItem, int parentId);
    void setupDB();
    QSqlDatabase db;
    QString databasePath;
private slots:
    void TreeItemClick();
signals:
    void dbIsOk();
};

#endif // MAINCONTROLLER_H
