#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QFileSystemModel>
#include <QMenuBar>
#include <QFont>
#include <QInputDialog>
#include <QDateTime>
#include <QShortcut>
#include <QDesktopServices>
#include <QUrl>
#include <QTextEdit>
#include <thread>
#include "QDebug"
#include "./../ui/ui_mainwindow.h"
#include "./include/utils/copy_path.h"
#include "./include/utils/dir_size.h"
#include "./include/global.h"
#include "./include/utils/navigation.h"
#include "./include/utils/search_filter.h"
#include "./include/utils/create_unit.h"
#include "./include/utils/filename.h"
#include "./include/utils/rename_unit.h"
#include "./include/utils/copypaste.h"
#include "./include/utils/delete_unit.h"
#include "./include/properties.h"
#include "./include/propertieswindow.h"


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
    void on_listView_doubleClicked(const QModelIndex &index);
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
};
#endif
