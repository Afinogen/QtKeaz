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
#include <QTableView>
#include <QHeaderView>
#include <QScrollArea>
#include "treeitem.h"
#include "treemodel.h"
#include "downloadmanager.h"
#include "components/model/tablemodel.h"
#include "components/delegate/tableimgdelegate.h"
#include "components/model/tablemodelstring.h"


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
    void setComponent(QLineEdit *searchText, QLabel *titleLabel, QTextEdit *descrText, QTableView *tableImg, QScrollArea *scrollArea);
    void setupTableSearchString(QString search);
public slots:
    void conDB();
private:
    void createTreeItem(TreeItem *parentItem, int parentId);
    void setupDB();
    void setupTableModelImg(int parentId);
    void setupTableModelString(int parentId);
    QSqlDatabase db;
    QString databasePath;
    QLineEdit *searchText;
    QLabel *titleLabel;
    QTextEdit *descrText;
    QTableView *tableImg;
    QAbstractItemDelegate *defultDelegate;
    TableImgDelegate *delegateForImg;
    TableModel *modelImg;
    TableModelString *modelString;
    QScrollArea *scrollArea;
private slots:
    void TreeItemClick(const QModelIndex &index);
    void TableImgItemClick(const QModelIndex  &index);
    void TableStringItemClick(const QModelIndex  &index);
signals:
    void dbIsOk();
};

#endif // MAINCONTROLLER_H
