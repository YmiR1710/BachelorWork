#ifndef DONUTBREAKDOWNCHART_H
#define DONUTBREAKDOWNCHART_H

#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>

QT_CHARTS_USE_NAMESPACE

class DonutBreakdownChart : public QChart
{
    Q_OBJECT
public:
    DonutBreakdownChart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = {});
    void addBreakdownSeries(QPieSeries *series, QColor color);

private:
    void recalculateAngles() const;
    void updateLegendMarkers() const;
    QPieSeries *m_mainSeries;
};

#endif
