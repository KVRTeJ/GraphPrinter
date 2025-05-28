#ifndef SPLINECHARTCREATOR_H
#define SPLINECHARTCREATOR_H

#include "IChartCreator.h"

#include <QtCharts/QChart>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QDateTime>

QT_CHARTS_USE_NAMESPACE

class SplineChartCreator : public IChartCreator {
public:
    SplineChartCreator() = default;

    QChart* create(const QList<GraphData>& data) override {
        QChart* chart = new QChart();
        chart->setTitle("Spline chart");

        QSplineSeries *series = new QSplineSeries();
        for (const auto& point : data) {
            series->append(point.xAxis, point.yAxis);
        }

        chart->addSeries(series);

        QDateTimeAxis *axisX = new QDateTimeAxis();
        axisX->setFormat("dd.MM.yyyy HH:mm");
        axisX->setTitleText("Дата");
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        QValueAxis *axisY = new QValueAxis();
        axisY->setTitleText("Значение");
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);

        return chart;
    }
};

#endif // SPLINECHARTCREATOR_H
