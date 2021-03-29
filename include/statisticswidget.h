#ifndef STATISTICSWIDGET_H
#define STATISTICSWIDGET_H

#include "../ui/ui_statisticswidget.h"
#include "./utils/statistics.h"
#include "./utils/dir_size.h"
#include "./discview.h"
#include "donutbreakdownchart.h"
#include "global.h"
#include "themes.h"
#include <QWidget>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>

namespace Ui {
class StatisticsWidget;
}

class StatisticsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticsWidget(QWidget *parent = nullptr);
    ~StatisticsWidget();

private slots:
    void paint_statistics(QFileInfo info);

signals:
    void update_charts(QFileInfo info);

private:
    Ui::StatisticsWidget *ui;
};

#endif
