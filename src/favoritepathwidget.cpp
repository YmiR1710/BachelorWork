#include "./include/favoritepathwidget.h"

FavoritePathWidget::FavoritePathWidget(QWidget *parent, QString path) :
    QWidget(parent),
    ui(new Ui::FavoritePathWidget)
{
    ui->setupUi(this);
    ui->okButton->setVisible(false);
    ui->lineEdit->setVisible(false);
    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(delete_widget()));
    connect(this, SIGNAL(clicked(QString)), parent->parentWidget()->parentWidget(), SLOT(open_favorite_path(QString)));
    connect(this, SIGNAL(clicked(QString)), parent->parentWidget(), SLOT(close_window()));
    connect(ui->editButton, SIGNAL(clicked()), this, SLOT(edit_path()));
    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(save_path()));
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(save_path()));
    ui->favoritePathWidgetLabel->setText(path);
}

FavoritePathWidget::~FavoritePathWidget()
{
    delete ui;
}

void FavoritePathWidget::delete_widget()
{
    this->deleteLater();
    existingFavoritePaths.removeOne(ui->favoritePathWidgetLabel->text());
}

void FavoritePathWidget::mousePressEvent(QMouseEvent *event)
{
    emit clicked(ui->favoritePathWidgetLabel->text());
}

void FavoritePathWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void FavoritePathWidget::edit_path()
{
    ui->lineEdit->setText(ui->favoritePathWidgetLabel->text());
    ui->lineEdit->selectAll();
    ui->favoritePathWidgetLabel->setVisible(false);
    ui->lineEdit->setVisible(true);
    ui->okButton->setVisible(true);
    ui->lineEdit->setFocus();
}

void FavoritePathWidget::save_path()
{
    if (validate(ui->lineEdit->text()) && !existingFavoritePaths.contains(ui->lineEdit->text())) {
        existingFavoritePaths.append(ui->lineEdit->text());
        existingFavoritePaths.removeOne(ui->favoritePathWidgetLabel->text());
        ui->favoritePathWidgetLabel->setText(ui->lineEdit->text());
        ui->lineEdit->setVisible(false);
        ui->lineEdit->clear();
        ui->okButton->setVisible(false);
        ui->favoritePathWidgetLabel->setVisible(true);
    } else if (ui->lineEdit->text() == ui->favoritePathWidgetLabel->text()) {
        ui->lineEdit->setVisible(false);
        ui->lineEdit->clear();
        ui->okButton->setVisible(false);
        ui->favoritePathWidgetLabel->setVisible(true);
    }
}

bool FavoritePathWidget::validate(QString path)
{
    if (QDir(path).exists() && !path.isEmpty()) {
        return true;
    }
    return false;
}
