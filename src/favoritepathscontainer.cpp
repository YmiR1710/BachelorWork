#include "./include/favoritepathscontainer.h"

FavoritePathsContainer::FavoritePathsContainer(QWidget *parent, QString defaultPath) :
    QWidget(parent),
    ui(new Ui::FavoritePathsContainer)
{
    ui->setupUi(this);
    ui->contentLayout->setAlignment(Qt::AlignTop);
    ui->lineEdit->setText(defaultPath);
    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(add_favorite_path()));
    connect(ui->favoritesPushButton, SIGNAL(clicked()), this, SLOT(add_favorite_path()));
    for (QString path : existingFavoritePaths) {
        FavoritePathWidget *newPath = new FavoritePathWidget(this, path);
        if (newPath->validate(path)) {
            ui->contentLayout->addWidget(newPath);
        }
    }
}

FavoritePathsContainer::~FavoritePathsContainer()
{
    delete ui;
}

void FavoritePathsContainer::add_favorite_path() {
    QString path = ui->lineEdit->text();
    FavoritePathWidget *newPath = new FavoritePathWidget(this, path);
    if (newPath->validate(path) && !existingFavoritePaths.contains(path)) {
        ui->lineEdit->setText("");
        ui->contentLayout->addWidget(newPath);
        existingFavoritePaths.append(path);
    }
}
