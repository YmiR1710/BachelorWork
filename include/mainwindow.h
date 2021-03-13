#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QFileSystemModel>
#include <QMenuBar>
#include <QMessageBox>
#include <QInputDialog>
#include <QDateTime>
#include <QShortcut>
#include <QDesktopServices>
#include <QUrl>
#include "QDebug"
#include "./include/global.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_listView_1_doubleClicked(const QModelIndex &index);
    void click(const QModelIndex &index);
    void show_hide_search_1();
    void show_hide_search_2();
    void close_search();
    void customMenuRequested(const QPoint &pos);
    void delete_file();
    void rename_file();
    void get_properties();
    void lineEditEnter();
    void searchEnter();
    void copy_file();
    void paste_file();
    void open_file();
    void cut_file();
    void create_file();
    void create_folder();


private:
    Ui::MainWindow *ui;
    QFileSystemModel *model;
    QFileSystemModel *model_2;
    qint64 dirSize(QString dirPath);
    void copyPath(QString src, QString dst);
};
#endif
