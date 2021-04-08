#include "./include/statisticswidget.h"

//QList<QColor> colorTheme = {QColor("#008232"), QColor("#F71100"), QColor("#9C00EB"), QColor("#3AD65C"), QColor("#000FF6")};
QList<QColor> colorTheme = {QColor("#3e3e3e"), QColor("#3e3e3e"), QColor("#3e3e3e"), QColor("#3e3e3e"), QColor("#3e3e3e")};

StatisticsWidget::StatisticsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticsWidget)
{
    ui->setupUi(this);
    ConfigParser::configure();
    currentChartsTheme = currentTheme;
    connect(this, SIGNAL(update_charts(QFileInfo)), this, SLOT(paint_statistics(QFileInfo)));
    QList<QStorageInfo> infoList = StatisticsUtils::get_storage_info();
    donutBreakdown = new DonutBreakdownChart();
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
        used->setBorderWidth(0);
        free->setBorderWidth(0);
        donutBreakdown->addBreakdownSeries(series, colorTheme[colorCounter]);
        donutBreakdown->legend()->hide();
        colorCounter++;
        if (colorCounter == colorTheme.size()) {
            colorCounter = 0;
        }
    }
    donutBreakdown->setContentsMargins(-60, -60, -60, -60);
    if (currentTheme == Theme::DARK) {
        donutBreakdown->setPlotAreaBackgroundBrush(QBrush(QColor("#2B2C2D")));
    }
    else if (currentTheme == Theme::LIGHT) {
        donutBreakdown->setPlotAreaBackgroundBrush(QBrush(QColor("#FFFFFF")));
    }
    donutBreakdown->setPlotAreaBackgroundVisible(true);
    ui->totalConsumption->setChart(donutBreakdown);
    ui->totalConsumption->setRenderHint(QPainter::Antialiasing);
    for (int i = 0; i < infoList.size(); i++) {
        QStorageInfo info = infoList[i];
        QString ready = info.isReady() ? "yes" : "no";
        QString readOnly = info.isReadOnly() ? "yes" : "no";
        DiscView *disc = new DiscView(this, "Disc: " + infoList[i].rootPath().remove(info.rootPath().size() - 2, info.rootPath().size()),
                                      "File system type: " + infoList[i].fileSystemType(),
                                      DirectorySizeCalculationUtils::getFormattedSize(info.bytesTotal() - info.bytesAvailable()) + " ",
                                      DirectorySizeCalculationUtils::getUnit(info.bytesTotal() - info.bytesAvailable()),
                                      DirectorySizeCalculationUtils::getFormattedSize(info.bytesTotal()) + " ",
                                      DirectorySizeCalculationUtils::getUnit(info.bytesTotal()),
                                      "Ready: " + ready,
                                      "ReadOnly: " + readOnly);
        ui->discs->addTab(disc, infoList[i].rootPath().remove(info.rootPath().size() - 2, info.rootPath().size()));
    }
    setup_cloud_drives();
}

StatisticsWidget::~StatisticsWidget()
{
    delete ui;
}

void StatisticsWidget::paint_statistics(QFileInfo info) {
    QPieSeries *series = new QPieSeries();
    QMapIterator<QString, int> it(StatisticsUtils::get_types_distribution_by_count(info));
    while (it.hasNext()) {
        it.next();
        series->append(it.key(), it.value());
        series->setLabelsVisible(true);
    }
    typesChart = new QChart();
    typesChart->addSeries(series);
    typesChart->legend()->hide();
    typesChart->setAnimationOptions(QChart::AllAnimations);
    if (currentTheme == Theme::DARK) {
        typesChart->setTheme(QChart::ChartThemeHighContrast);
        for (QPieSlice *slice : series->slices()) {
            slice->setLabelColor(QColor("#BABABF"));
        }
        typesChart->setPlotAreaBackgroundBrush(QBrush(QColor("#2B2C2D")));
    }
    else if (currentTheme == Theme::LIGHT) {
        typesChart->setTheme(QChart::ChartThemeHighContrast);
        for (QPieSlice *slice : series->slices()) {
            slice->setLabelColor(QColor("#101012"));
        }
        typesChart->setPlotAreaBackgroundBrush(QBrush(QColor("#FFFFFF")));
    }
    typesChart->setContentsMargins(-40, -40, -40, -40);
    typesChart->setPlotAreaBackgroundVisible(true);
    ui->typesDistribution->setChart(typesChart);
    ui->typesDistribution->setRenderHint(QPainter::Antialiasing);
}

void StatisticsWidget::setup_cloud_drives() {
    QList<CloudDrive> drives = CloudDriveUtils::get_supported_drives();
    for (auto drive : drives) {
        CloudDriveWidget *driveWidget = new CloudDriveWidget(this->parentWidget()->parentWidget()->parentWidget()->parentWidget(), drive.getName(), drive.getImage(), DirectorySizeCalculationUtils::formatSize(drive.getSize()));
        ui->verticalLayout->insertWidget(0, driveWidget);
    }
}

void StatisticsWidget::updateChartsTheme(Theme theme) {
    if (currentChartsTheme != theme) {
        if (theme == Theme::DARK) {
            typesChart->setTheme(QChart::ChartThemeHighContrast);
            typesChart->setPlotAreaBackgroundBrush(QBrush(QColor("#2B2C2D")));
            donutBreakdown->setPlotAreaBackgroundBrush(QBrush(QColor("#2B2C2D")));
        }
        else if (theme == Theme::LIGHT) {
            typesChart->setTheme(QChart::ChartThemeHighContrast);
            typesChart->setPlotAreaBackgroundBrush(QBrush(QColor("#FFFFFF")));
            donutBreakdown->setPlotAreaBackgroundBrush(QBrush(QColor("#FFFFFF")));
        }
        currentChartsTheme = theme;
    }
}
