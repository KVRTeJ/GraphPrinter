#ifndef LINEPRINTER_H
#define LINEPRINTER_H

#include <QtCharts/QChartGlobal>

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLegend>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtCore/QTime>
#include <QtCharts/QBarCategoryAxis>
#include <QDateTimeAxis>
#include <QValueAxis>

#include "AbstractParser.h" //GraphData

#include <QDateTime>

QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE
class LinePrinter {
public:
    LinePrinter() = default;

    QChart* get(QList<GraphData>* _data) {
        QChart* chart = new QChart();
        chart->setTitle("Line chart");

        QLineSeries *series = new QLineSeries();
        for (const auto &point : *_data) {
            qint64 msecsSinceEpoch = point.xAxis.toMSecsSinceEpoch();
            series->append(msecsSinceEpoch, point.yAxis);
        }

        chart->addSeries(series);
        chart->setTitle("График с QDateTime на оси X");

        // Настраиваем ось X (временная)
        QDateTimeAxis *axisX = new QDateTimeAxis();
        axisX->setFormat("dd.MM.yyyy"); // Формат даты
        axisX->setTitleText("Дата");
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        // Настраиваем ось Y (числовая)
        QValueAxis *axisY = new QValueAxis();
        axisY->setTitleText("Значение");
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);

        return chart;
    }

private:
    // QList<GraphData>* _data = nullptr;
};

#endif // LINEPRINTER_H
