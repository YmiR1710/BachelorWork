#include "./include/favoritesmainwindow.h"

FavoritesMainWindow::FavoritesMainWindow(QWidget *parent) : QMainWindow(parent)
{

}

void FavoritesMainWindow::closeEvent(QCloseEvent *event)
{
    ConfigParser::change_config("favorites", ConfigParser::list_to_string(existingFavoritePaths));
    event->accept();
}

void FavoritesMainWindow::close_window()
{
    close();
}

