#include "./include/statisticswidget.h"

//QList<QColor> colorTheme = {QColor("#008232"), QColor("#F71100"), QColor("#9C00EB"), QColor("#3AD65C"), QColor("#000FF6")};
QList<QColor> colorTheme = {QColor("#3e3e3e"), QColor("#3e3e3e"), QColor("#3e3e3e"), QColor("#3e3e3e"), QColor("#3e3e3e")};

StatisticsWidget::StatisticsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticsWidget)
{
    ui->setupUi(this);
    connect(this, SIGNAL(update_charts(QFileInfo)), this, SLOT(paint_statistics(QFileInfo)));
    QList<QStorageInfo> infoList = StatisticsUtils::get_storage_info();
    DonutBreakdownChart *donutBreakdown = new DonutBreakdownChart();
    donutBreakdown->setAnimationOptions(QChart::AllAnimations);
    donutBreakdown->legend()->setAlignment(Qt::AlignRight);
    int colorCounter = 0;
    for (QStorageInfo info : infoList) {
        QPieSeries *series = new QPieSeries();
        series->setName(QString("%1 %2").arg(info.rootPath()).arg(DirectorySizeCalculationUtils::formatSize(info.bytesTotal())));
        series->append("Free space", info.bytesAvailable());
        series->append("Used space", info.bytesTotal() - info.bytesAvailable());
        QPieSlice *used = series->slices().at(0);
        QPieSlice *free = series->slices().at(1);
        used->setLabelVisible(false);
        free->setLabelVisible(false);
        donutBreakdown->addBreakdownSeries(series, colorTheme[colorCounter]);
        donutBreakdown->legend()->hide();
        colorCounter++;
        if (colorCounter == colorTheme.size()) {
            colorCounter = 0;
        }
    }
    ui->totalConsumption->setChart(donutBreakdown);
    ui->totalConsumption->setRenderHint(QPainter::Antialiasing);

    for (int i = 0; i < infoList.size(); i++) {
        QStorageInfo info = infoList[i];
        DiscView *disc = new DiscView(this, "Name: " + infoList[i].rootPath().remove(info.rootPath().size() - 2, info.rootPath().size()),
                                      "File system type: " + infoList[i].fileSystemType(),
                                      DirectorySizeCalculationUtils::formatSize(info.bytesAvailable()) + " free of " + DirectorySizeCalculationUtils::formatSize(info.bytesTotal()));
        ui->discs->addTab(disc, infoList[i].rootPath().remove(info.rootPath().size() - 2, info.rootPath().size()));
    }
}

void StatisticsWidget::paint_statistics(QFileInfo info) {
    QPieSeries *series = new QPieSeries();
    QMapIterator<QString, int> it(StatisticsUtils::get_types_distribution_by_count(info));
    while (it.hasNext()) {
        it.next();
        series->append(it.key(), it.value());
        series->setLabelsVisible(true);
    }
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setTheme(QChart::ChartThemeHighContrast);
    ui->typesDistribution->setChart(chart);
    ui->typesDistribution->setRenderHint(QPainter::Antialiasing);
}

StatisticsWidget::~StatisticsWidget()
{
    delete ui;
}
