#ifndef SCATTERCHARTCREATOR_H
#define SCATTERCHARTCREATOR_H

#include "IChartCreator.h"

#include <QtCharts/QChart>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QDateTime>

QT_CHARTS_USE_NAMESPACE

class ScatterChartCreator : public IChartCreator {
public:
    ScatterChartCreator() = default;

    QChart* create(const QList<GraphData>& data) override {
        QChart* chart = new QChart();
        chart->setTitle("Scatter chart");

        QScatterSeries *series = new QScatterSeries();
        for (const auto& point : data) {
            series->append(point.xAxis, point.yAxis);
        }

        series->setMarkerSize(5.0);
        series->setMarkerShape(QScatterSeries::MarkerShapeCircle);

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

#endif // SCATTERCHARTCREATOR_H
