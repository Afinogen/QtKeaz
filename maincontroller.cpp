#include "maincontroller.h"

MainController::MainController(QObject *parent):QObject(parent)
{
}
MainController::~MainController()
{

}
void MainController::connectDB()
{
    QString tmpString = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    QFileInfo databaseFileInfo(QString("%1/%2").arg(tmpString).arg("keaz.db"));
    databasePath = databaseFileInfo.absoluteFilePath();
    qDebug() << "databasePath: "+databasePath;  // to display full name with path of databas
    if (!databaseFileInfo.exists()) setupDB();
    else if (!db.isOpen())
    {
        conDB();
    }
    else
    {
        qDebug()<<"db is open";
    }
}
void MainController::closeDB()
{
    qDebug() << "close db ";
    db.close();
}
TreeModel *MainController::createTreeView()
{
    TreeModel *model = new TreeModel();
    createTreeItem(model->getRoot(),1);
    return model;
}
void MainController::createTreeItem(TreeItem *parentItem, int parentId)
{
    QSqlQuery qry;
    qDebug() << "SELECT * FROM `product_category` WHERE `parent_id`='"+QString("%1").arg(parentId)+"';";
    if (qry.exec("SELECT * FROM `product_category` WHERE `parent_id`='"+QString("%1").arg(parentId)+"';"))
    {
        // если запрос выполнен, то запускаем цикл перехода по каждой
        // строке
        while(qry.next())
        {
            TreeItem *item = new TreeItem(qry.value(0).toInt(),QString(qry.value(4).toString()),parentItem);
            parentItem->appendChild(item);
            createTreeItem(item,qry.value(0).toInt());
        }
    }
    else
    {
        qDebug() << qry.lastError();
    }
}
void MainController::TreeItemClick(const QModelIndex  &index)
{
    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    qDebug() << "item click " << item->getDbId() << item->data();
    QSqlQuery qry;
    qDebug() << "SELECT * FROM `product_category` WHERE `product_category_id`='"+QString("%1").arg(item->getDbId())+"';";
    if (qry.exec("SELECT * FROM `product_category` WHERE `product_category_id`='"+QString("%1").arg(item->getDbId())+"';"))
    {
        qry.next();
        titleLabel->setText(qry.value(4).toString());
        qry.clear();
        qry.exec("SELECT * FROM `product_category_description` WHERE `product_category_id`='"+QString("%1").arg(item->getDbId())+"';");
        qry.next();
        descrText->setText(qry.value(3).toString());
    }
    else
    {
        qDebug() << qry.lastError();
    }
}
void MainController::setupDB()
{
        qDebug()<<"Database does not exist";
        #ifdef Q_OS_ANDROID
        bool copySuccess = QFile::copy( QString("assets:/keaz.db"), databasePath );
        if ( !copySuccess )
        {
            DownloadManager *d2=new DownloadManager();
            d2->downList.append("http://skynet.meximas.com/keaz.db");
            d2->saveList.append(databasePath);
            MainController::connect(d2,SIGNAL(isDownload()),SLOT(conDB()));
            QTimer::singleShot(0, d2, SLOT(execute()));
        }
        #else
        DownloadManager *d2=new DownloadManager();
        d2->downList.append("http://skynet.meximas.com/keaz.db");
        d2->saveList.append(databasePath);
        MainController::connect(d2,SIGNAL(isDownload()),SLOT(conDB()));
        QTimer::singleShot(0, d2, SLOT(execute()));
        #endif
}
void MainController::conDB()
{
    qDebug() << "begin connect db";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(databasePath);
    qDebug() << "open db: " << db.open();
    dbIsOk();
}
bool MainController::isConnectedDB()
{
    return db.isOpen();
}
void MainController::setComponent(QLineEdit *searchText,QLabel *titleLabel,QTextEdit *descrText)
{
    this->searchText=searchText;
    this->titleLabel=titleLabel;
    this->descrText=descrText;
}
