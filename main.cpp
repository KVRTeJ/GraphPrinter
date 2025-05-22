#include <iostream>

#include "IParser.h"
#include "SqlLiteParser.h"
#include "JsonParser.h"
#include "DataExtract.h"


#include <qdebug.h>
int main(int argc, char *argv[]) {
    GraphDataExtracter ext;

    JsonParser jPar;
    jPar.setDataExtracter(&ext);


    SqlLiteParser par;
    par.setDataExtracter(&ext);

    IParser<QVector<GraphData>>* iJPar = &jPar;
    iJPar->setFilePath("/Users/dmitriy/data/BLOOD_SUGAR.json");
    iJPar->parse();

    par.setFilePath("/Users/dmitriy/data/BLOOD_SUGAR.sqlite");
    par.parse();

    QVector<GraphData> jsonData = iJPar->getData();
    QVector<GraphData> sqlData = par.getData();

    for(auto it = sqlData.begin(), jt = jsonData.begin(); it != sqlData.end(); ++it, ++jt) {
        qDebug() << it->xAxis << jt->xAxis << '\t' << it->yAxis << jt->yAxis;
        assert(it->xAxis == jt->xAxis);
        assert(it->yAxis == jt->yAxis);
    }

    qDebug() << "\n=-=-=-=-=-=--=\n\n";

    for(auto it = sqlData.begin(), jt = jsonData.begin(); it != sqlData.end(); ++it, ++jt) {
        qDebug() << it->xAxis << jt->xAxis << '\t' << it->yAxis << jt->yAxis;
        assert(it->xAxis == jt->xAxis);
        assert(it->yAxis == jt->yAxis);
    }

    return 1;

    par.setFilePath("/Users/dmitriy/data/TEMPERATURE_NOVOSIB.sqlite");
    jPar.setFilePath("/Users/dmitriy/data/TEMPERATURE_NOVOSIB.json");
    par.parse();
    jPar.parse();

    jsonData = jPar.getData();
    sqlData = par.getData();

    for(auto it = sqlData.begin(), jt = jsonData.begin(); it != sqlData.end(); ++it, ++jt) {
        qDebug() << it->xAxis << jt->xAxis << '\t' << it->yAxis << jt->yAxis;
    }

    par.setFilePath("/Users/dmitriy/data/PRICES_NATURAL_GAS_USD.sqlite");
    jPar.setFilePath("/Users/dmitriy/data/PRICES_NATURAL_GAS_USD.json");
    par.parse();
    jPar.parse();

    jsonData = jPar.getData();
    sqlData = par.getData();

    for(auto it = sqlData.begin(), jt = jsonData.begin(); it != sqlData.end(); ++it, ++jt) {
        qDebug() << it->xAxis << jt->xAxis << '\t' << it->yAxis << jt->yAxis;
        assert(it->xAxis == jt->xAxis);
        assert(it->yAxis == jt->yAxis);
    }

    par.setFilePath("/Users/dmitriy/data/NORDPOOL_PRICES.sqlite");
    jPar.setFilePath("/Users/dmitriy/data/NORDPOOL_PRICES.json");
    par.parse();
    jPar.parse();

    jsonData = jPar.getData();
    sqlData = par.getData();

    for(auto it = sqlData.begin(), jt = jsonData.begin(); it != sqlData.end(); ++it, ++jt) {
        qDebug() << it->xAxis << jt->xAxis << '\t' << it->yAxis << jt->yAxis;
        assert(it->xAxis == jt->xAxis);
        assert(it->yAxis == jt->yAxis);
    }

    par.setFilePath("/Users/dmitriy/data/HUMIDITY_MOSCOW.sqlite");
    jPar.setFilePath("/Users/dmitriy/data/HUMIDITY_MOSCOW.json");
    par.parse();
    jPar.parse();

    jsonData = jPar.getData();
    sqlData = par.getData();

    for(auto it = sqlData.begin(), jt = jsonData.begin(); it != sqlData.end(); ++it, ++jt) {
        qDebug() << it->xAxis << jt->xAxis << '\t' << it->yAxis << jt->yAxis;
        assert(it->xAxis == jt->xAxis);
        assert(it->yAxis == jt->yAxis);
    }

    jPar.setFilePath("/Users/dmitriy/data/HUMIDITY_MOSCOW_beat.json");
    jPar.parse();
}
