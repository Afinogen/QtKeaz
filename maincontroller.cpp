#include "maincontroller.h"

MainController::MainController(QObject *parent):QObject(parent)
{
    delegateForImg=new TableImgDelegate();
    modelImg=new TableModel();
    modelString=new TableModelString();
    QString tmpString = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    QFileInfo path(QString("%1/%2").arg(tmpString).arg("KEAZ/files"));
    QDir dir;
    dir.mkpath(path.absoluteFilePath());
}
MainController::~MainController()
{
    delete delegateForImg;
    delete modelImg;
    delete modelString;
    closeDB();
}
void MainController::connectDB()
{
    QString tmpString = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    QFileInfo databaseFileInfo(QString("%1/%2").arg(tmpString).arg("KEAZ/keaz.db"));
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
    if (qry.exec("SELECT * FROM `product_category` WHERE `parent_id`='"+QString("%1").arg(parentId)+"'  AND `is_deleted`='0';"))
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
    setVisibleItem(false);
    setVisibleSearch(true);
    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    qDebug() << "item click " << item->getDbId() << item->data();
    QSqlQuery qry;
    //qDebug() << "SELECT * FROM `product_category` WHERE `product_category_id`='"+QString("%1").arg(item->getDbId())+"';";
    if (qry.exec("SELECT * FROM `product_category` WHERE `product_category_id`='"+QString("%1").arg(item->getDbId())+"';"))
    {
        qry.next();
        titleLabel->setText(qry.value(4).toString());
        if (qry.value(1).toInt()==1) {
            setupTableModelImg(item->getDbId());
            this->graphicsView->setVisible(false);
        }
        else {
            setupTableModelString(item->getDbId());
            this->graphicsView->setVisible(true);
        }
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
            d2->downList.append("http://test.keaz.ru/keaz.db");
            d2->saveList.append(databasePath);
            MainController::connect(d2,SIGNAL(isDownload()),SLOT(conDB()));
            QTimer::singleShot(0, d2, SLOT(execute()));
        }
        #else
        DownloadManager *d2=new DownloadManager(this);
        d2->setStatusBar(bar);
        d2->downList.append("http://test.keaz.ru/keaz.db");
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
void MainController::setComponent(QLineEdit *searchText, QLabel *titleLabel, QTextEdit *descrText, QTableView *tableImg, QScrollArea *scrollArea, QGraphicsView *graphicsView, QStatusBar *bar)
{
    this->searchText=searchText;
    this->titleLabel=titleLabel;
    this->descrText=descrText;
    this->tableImg=tableImg;
    this->scrollArea=scrollArea;
    this->graphicsView=graphicsView;
    this->defultDelegate=this->tableImg->itemDelegate();
    this->titleLabel->setText("");
    this->graphicsView->setScene(new QGraphicsScene(this));
    //this->pixmapDescr = this->graphicsView->scene()->addPixmap(QPixmap(QSize(300,300)));
    this->graphicsView->setVisible(false);
    this->bar=bar;
}
void MainController::setupTableModelImg(int parentId)
{
    TableModel *model=new TableModel();
    if (this->modelImg!=NULL) delete this->modelImg;
    this->modelImg=model;
    //modelImg->clearModel();
    QSqlQuery qry;
    //qDebug()<<"SELECT * FROM `product_category` WHERE `parent_id`='"+QString("%1").arg(parentId)+"';";
    qDebug()<<"SELECT `product_category`.*, `file`.`file_id`, `file`.`file_path`,`file`.`file_ext`,`file`.`filename` FROM `product_category`, `file` WHERE `file`.`file_id`=`product_category`.`file_id` AND `parent_id`='"+QString("%1").arg(parentId)+"';";
    if (qry.exec("SELECT `product_category`.*, `file`.`file_id`, `file`.`file_path`,`file`.`file_ext`,`file`.`filename` FROM `product_category`, `file` WHERE `file`.`file_id`=`product_category`.`file_id` AND `parent_id`='"+QString("%1").arg(parentId)+"';"))
    {
        QString path = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);

        while (qry.next()) {
            QDir dir;
            DownloadManager *d2=new DownloadManager(this);
            d2->setStatusBar(bar);
            QFileInfo fileInfo(QString("%1/KEAZ/files/%2/%3.%4").arg(path).arg(qry.value(8).toString()).arg(qry.value(6).toString()).arg(qry.value(9).toString()));
            dir.mkpath(fileInfo.absolutePath());
           // qDebug()<<qry.value(4).toString()<<" "<<" "<<qry.value(5).toString()<<qry.value(6).toString()<<" "<<qry.value(7).toString()<<" "<<qry.value(8).toString()<<" "<<qry.value(9).toString();
           // qDebug()<<fileInfo.absoluteFilePath();
            if (fileInfo.exists()) {
                model->addItem(qry.value(0).toInt(), qry.value(4).toString(),fileInfo.absoluteFilePath());
            } else {
                d2->downList.append("http://keaz.ru/f/"+qry.value(6).toString()+"/"+qry.value(10).toString());
                d2->saveList.append(fileInfo.absoluteFilePath());
                //MainController::connect(d2,SIGNAL(isDownload()),SLOT(conDB()));
                model->addItem(qry.value(0).toInt(), qry.value(4).toString(),"/home/afinogen/qt_project/build-QtKeaz-Desktop_Qt_5_3_GCC_64bit-Debug/vm63-2-bcd-1.png");
            }
            if (d2->downList.size()>0) {
                QTimer::singleShot(0, d2, SLOT(execute()));
            }
        }

        this->tableImg->setModel(model);
        tableImg->setItemDelegate(delegateForImg);
        this->tableImg->setColumnWidth(0,300);
        for(int i=0;i<model->rowCount();i++)
            this->tableImg->setRowHeight(i,300);
        this->tableImg->horizontalHeader()->setVisible(false);
        disconnect(this->tableImg,SIGNAL(clicked(const QModelIndex  &)),this,NULL);
        connect(this->tableImg, SIGNAL(clicked(const QModelIndex  &)),this, SLOT(TableImgItemClick(const QModelIndex  &)));
        this->descrText->setMaximumHeight(200);
        //this->scrollArea   ->setGeometry(0,0,this->scrollArea->width(),this->tableImg->height()+1000);
    }
    else qDebug()<<qry.lastError();
}
/**
 * @brief MainController::setupTableModelString
 * @param int parentId
 */
void MainController::setupTableModelString(int parentId)
{
    TableModelString *model = new TableModelString();

    QSqlQuery qry;
    if (qry.exec("SELECT * FROM `product` WHERE `product_category_id`='"+QString("%1").arg(parentId)+"';"))
    {
        while (qry.next()) {
            qDebug()<<qry.value(5).toString();
            model->addItem(qry.value(5).toString(),qry.value(0).toString());
        }

        this->tableImg->horizontalHeader()->setVisible(true);
        this->tableImg->setColumnWidth(0,500);

        this->tableImg->setModel(model);
        this->tableImg->setItemDelegate(this->defultDelegate);

        for(int i=0;i<model->rowCount();i++)
            this->tableImg->setRowHeight(i,40);
        disconnect(this->tableImg,SIGNAL(clicked(const QModelIndex  &)),this,NULL);
        connect(this->tableImg, SIGNAL(clicked(const QModelIndex  &)),this, SLOT(TableStringItemClick(const QModelIndex  &)));
        this->descrText->setMaximumHeight(400);
    }
    else qDebug()<<qry.lastError();
}
void MainController::TableImgItemClick(const QModelIndex &index)
{
    setVisibleItem(false);
    setVisibleSearch(true);
    TableItem *item = this->modelImg->getItem(this->tableImg->model()->columnCount()*index.row()+index.column());
    qDebug()<<item->title;
    QSqlQuery qry;
    //qDebug() << "SELECT * FROM `product_category` WHERE `product_category_id`='"+QString("%1").arg(item->getDbId())+"';";
    if (qry.exec("SELECT * FROM `product_category` WHERE `product_category_id`='"+QString("%1").arg(item->id)+"';"))
    {
        qry.next();
        titleLabel->setText(qry.value(4).toString());
        this->setupTableModelString(item->id);
        this->graphicsView->setVisible(true);

        this->graphicsView->scene()->addPixmap(QPixmap(item->file));

        qry.clear();
        qry.exec("SELECT * FROM `product_category_description` WHERE `product_category_id`='"+QString("%1").arg(item->id)+"';");
        qry.next();
        descrText->setText(qry.value(3).toString());
    }
    else
    {
        qDebug() << qry.lastError();
    }
    this->setupTableModelString(item->id);
}
void MainController::TableStringItemClick(const QModelIndex &index)
{
    setVisibleItem(true);
}
void MainController::setupTableSearchString(QString search)
{
    setVisibleItem(false);
    setVisibleSearch(false);
    TableModelString *model = new TableModelString();

    QSqlQuery qry;
    if (qry.exec("SELECT * FROM `product` WHERE `product_id` LIKE '%"+search+"%' OR `name` LIKE '%"+search+"%';"))
    {
        while (qry.next()) {
            qDebug()<<qry.value(5).toString();
            model->addItem(qry.value(5).toString(),qry.value(0).toString());
        }
        this->titleLabel->setText("Найдено "+QString("%1").arg(model->rowCount()) +" наименований");

        this->tableImg->horizontalHeader()->setVisible(true);
        this->tableImg->setColumnWidth(0,500);

        this->tableImg->setModel(model);
        this->tableImg->setItemDelegate(this->defultDelegate);

        for(int i=0;i<model->rowCount();i++)
            this->tableImg->setRowHeight(i,40);
        disconnect(this->tableImg,SIGNAL(clicked(const QModelIndex  &)),this,NULL);
        connect(this->tableImg, SIGNAL(clicked(const QModelIndex  &)),this, SLOT(TableStringItemClick(const QModelIndex  &)));
    }
    else qDebug()<<qry.lastError();
}
void MainController::setVisibleSearch(bool visible)
{
    this->descrText->setVisible(visible);
    this->graphicsView->setVisible(visible);
    //this->titleLabel->setVisible(visible);
}
void MainController::setVisibleItem(bool visible)
{
    this->descrText->setVisible(visible);
    this->tableImg->setVisible(!visible);
    if (visible)
    {
        this->descrText->setMaximumHeight(16777215);
    }
    else
    {
        this->descrText->setMaximumHeight(200);
    }
}
