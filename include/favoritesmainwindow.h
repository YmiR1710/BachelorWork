#ifndef FAVORITESMAINWINDOW_H
#define FAVORITESMAINWINDOW_H

#include "./include/utils/config_parser.h"
#include "global.h"
#include <QMainWindow>
#include <QCloseEvent>

class FavoritesMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit FavoritesMainWindow(QWidget *parent = nullptr);

protected:
    virtual void closeEvent(QCloseEvent *event) override;
};

#endif
