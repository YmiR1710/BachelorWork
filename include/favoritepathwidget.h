#ifndef FAVORITEPATHWIDGET_H
#define FAVORITEPATHWIDGET_H

#include "../ui/ui_favoritepathwidget.h"
#include "global.h"
#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include <QDir>
#include <QLineEdit>

namespace Ui {
class FavoritePathWidget;
}

class FavoritePathWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FavoritePathWidget(QWidget *parent = nullptr, QString path = "");
    ~FavoritePathWidget();
    bool validate(QString path);

protected:
    virtual void mousePressEvent (QMouseEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

private:
    Ui::FavoritePathWidget *ui;

private slots:
    void delete_widget();
    void edit_path();
    void save_path();

signals:
    void clicked(QString path);
};

#endif
