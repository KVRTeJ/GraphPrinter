#include "ApplicationWindow.h"

#include <QApplication>

#include <QDebug>

#include "SqlLiteParser.h"
#include "DataExtract.h"

#include "LineChartCreator.h"
#include "AreaChartCreator.h"
#include "ScatterChartCreator.h"
#include "SplineChartCreator.h"

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

    ApplicationWindow w;

    w.displayChart(line);
    w.show();

    return a.exec();
}
