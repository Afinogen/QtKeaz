#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QFileInfo>
#include <QStandardPaths>
#include <QLineEdit>
#include <QLabel>
#include <QTextEdit>
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
    void setComponent(QLineEdit *searchText, QLabel *titleLabel, QTextEdit *descrText);
public slots:
    void conDB();
private:
    void createTreeItem(TreeItem *parentItem, int parentId);
    void setupDB();
    QSqlDatabase db;
    QString databasePath;
    QLineEdit *searchText;
    QLabel *titleLabel;
    QTextEdit *descrText;
private slots:
    void TreeItemClick(const QModelIndex &index);
signals:
    void dbIsOk();
};

#endif // MAINCONTROLLER_H
