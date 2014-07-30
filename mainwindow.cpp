#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createMenus();
    setupMainController();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::createMenus()
{
    QMenu * mnFile = new QMenu("File"); // создаём меню Файл
    // ----------- здесь добавляем пункт меню и подключаем его к слоту----
    QAction * mnEdit = new QAction("Пуск",mnFile); // создаём меню Edit
    connect(mnEdit, SIGNAL(triggered()), this, SLOT(connectDB()));
    mnFile->addAction(mnEdit);
    QAction *msgAction = new QAction("Exit",mnFile);
    connect(msgAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    mnFile->addAction(msgAction);
    QMenu * mnService = new QMenu("Service"); // Меню Сервис
    QMenu * mnHelp = new QMenu("Help"); // Меню помощь
    ui->menuBar->addMenu(mnFile); // Добавляем пункты меню в menuBar, т.е. те, которые будут отображаться в гл. окне
    //ui->menuBar->addMenu(mnEdit);
    ui->menuBar->addMenu(mnService);
    ui->menuBar->addMenu(mnHelp);
}
void MainWindow::connectDB()
{
    mainC->connectDB();
    if (mainC->isConnectedDB())
    {
        setupTreeModel();
    }
    else
    {
        connect(mainC,SIGNAL(dbIsOk()),this,SLOT(setupTreeModel()));
    }
}
void MainWindow::setupTreeModel()
{
    ui->treeView->setModel(mainC->createTreeView());
    connect(ui->treeView, SIGNAL(clicked(const QModelIndex  &)),mainC, SLOT(TreeItemClick(const QModelIndex  &)));
    ui->treeView->show();
}
void MainWindow::setupMainController()
{
    mainC=new MainController(this);
    mainC->setComponent(ui->searchEdit,ui->titleLabel,ui->desrcText, ui->tableView,ui->scrollArea,ui->graphicsView,ui->statusBar);
    connectDB();
}

void MainWindow::on_searchEdit_textChanged(const QString &arg1)
{
    if (!arg1.isEmpty()) mainC->setupTableSearchString(arg1);
}

void MainWindow::on_searchEdit_returnPressed()
{
    if (!ui->searchEdit->text().isEmpty()) mainC->setupTableSearchString(ui->searchEdit->text());
}
