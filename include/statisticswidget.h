#ifndef STATISTICSWIDGET_H
#define STATISTICSWIDGET_H

#include "../ui/ui_statisticswidget.h"
#include "./utils/statistics.h"
#include "./utils/dir_size.h"
#include "./discview.h"
#include "./include/utils/cloud_drives.h"
#include "./include/cloud_drive_entity.h"
#include "./include/clouddrivewidget.h"
#include "./include/clouddrivewidget.h"
#include "./include/utils/config_parser.h"
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
    void updateChartsTheme(Theme theme);

private slots:
    void paint_statistics(QFileInfo info);

signals:
    void update_charts(QFileInfo info);

private:
    void setup_cloud_drives();
    Ui::StatisticsWidget *ui;
    Theme currentChartsTheme;
    DonutBreakdownChart *donutBreakdown;
    QChart *typesChart;
};

#endif
