#ifndef FAVORITEPATHSCONTAINER_H
#define FAVORITEPATHSCONTAINER_H

#include "../ui/ui_favoritepathscontainer.h"
#include "./include/favoritepathwidget.h"
#include "./include/utils/config_parser.h"
#include "global.h"
#include <QWidget>
#include <QCloseEvent>
#include <QShortcut>

namespace Ui {
class FavoritePathsContainer;
}

class FavoritePathsContainer : public QWidget
{
    Q_OBJECT

public:
    explicit FavoritePathsContainer(QWidget *parent = nullptr, QString defaultPath = "");
    ~FavoritePathsContainer();

public slots:
    void add_favorite_path();

private:
    Ui::FavoritePathsContainer *ui;
};

#endif
