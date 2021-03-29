#ifndef DISCVIEW_H
#define DISCVIEW_H

#include "../ui/ui_discview.h"
#include <QWidget>
#include <QString>

namespace Ui {
class DiscView;
}

class DiscView : public QWidget
{
    Q_OBJECT

public:
    explicit DiscView(QWidget *parent = nullptr, QString discName = "", QString systemType = "", QString memory = "");
    ~DiscView();

private:
    Ui::DiscView *ui;
};

#endif
