#include "ApplicationWindow.h"

#include <QApplication>

#include "SqlLiteParser.h"
#include "DataExtract.h"

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

    double max = data.begin()->yAxis;
    double min = data.begin()->yAxis;
    for(auto it = data.begin(); it != data.end(); ++it) {
        if (it->yAxis <min) min = it->yAxis;
        if (it->yAxis > max) max = it->yAxis;
    }

    qDebug() << max << min;
    ApplicationWindow foo(&data);
    foo.show();

    return 0;
}
