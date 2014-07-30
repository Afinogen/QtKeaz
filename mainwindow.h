#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "maincontroller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createMenus();
    void setupMainController();
private:
    Ui::MainWindow *ui;
    MainController *mainC;
private slots:
    void connectDB();
    void setupTreeModel();
    void on_searchEdit_textChanged(const QString &arg1);
    void on_searchEdit_returnPressed();
};

#endif // MAINWINDOW_H
