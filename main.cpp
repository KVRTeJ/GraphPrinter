#include "ApplicationWindow.h"

#include <QApplication>

#include "SqlLiteParser.h"
#include "DataExtract.h"

#include "LineChartCreator.h"
#include "AreaChartCreator.h"
#include "ScatterChartCreator.h"
#include "SplineChartCreator.h"

#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    SqlLiteParser par;
    GraphDataExtracter ext;
    par.setDataExtracter(&ext);
    par.setFilePath("/Users/dmitriy/data/BLOOD_SUGAR.sqlite");
    par.parse();

    DataModel model;
    model.setData(par.getData());
    auto data = model.getData();

    LineChartCreator lineChartCreator;
    auto line = lineChartCreator.create(data);

    QtCharts::QChartView* view = new QtCharts::QChartView(line);
    view->show();

    // AreaChartCreator areaChartCreator;
    // auto area = areaChartCreator.create(data);

    // view = new QtCharts::QChartView(area);
    // view->show();

    // ScatterChartCreator scatChartCreator;
    // auto scat = scatChartCreator.create(data);

    // view = new QtCharts::QChartView(scat);
    // view->show();

    // SplineChartCreator splineChartCreator;
    // auto spline = splineChartCreator.create(data);

    // view = new QtCharts::QChartView(spline);
    // view->show();

    return a.exec();
}
