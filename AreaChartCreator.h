#ifndef AREACHARTCREATOR_H
#define AREACHARTCREATOR_H

#include "IChartCreator.h"

#include <QtCharts/QChart>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QDateTime>

QT_CHARTS_USE_NAMESPACE

class AreaChartCreator : public IChartCreator {
public:
    AreaChartCreator() = default;

    QChart* create(const QList<GraphData>& data) override {
        QChart* chart = new QChart();
        chart->setTitle("Area chart");

        QLineSeries *upperSeries = new QLineSeries();
        for (const auto& point : data) {
            upperSeries->append(point.xAxis, point.yAxis);
        }

        QLineSeries *lowerSeries = new QLineSeries();
        for (const auto& point : data) {
            lowerSeries->append(point.xAxis, 0);
        }

        QAreaSeries *areaSeries = new QAreaSeries(upperSeries, lowerSeries);

        chart->addSeries(areaSeries);

        QDateTimeAxis *axisX = new QDateTimeAxis();
        axisX->setFormat("dd.MM.yyyy HH:mm");
        axisX->setTitleText("Дата");
        chart->addAxis(axisX, Qt::AlignBottom);
        areaSeries->attachAxis(axisX);

        QValueAxis *axisY = new QValueAxis();
        axisY->setTitleText("Значение");
        chart->addAxis(axisY, Qt::AlignLeft);
        areaSeries->attachAxis(axisY);

        return chart;
    }
};

#endif // AREACHARTCREATOR_H
