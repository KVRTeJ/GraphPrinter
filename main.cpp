#include <iostream>

#include "SqlLiteParser.h"
#include "DataExtract.h"

int main(int argc, char *argv[]) {
    SqlLiteParser par;
    GraphDataExtracter ext;
    par.setDataExtracter(&ext);

    par.setFilePath("/Users/dmitriy/data/BLOOD_SUGAR.sqlite");
    par.parse();

    par.setFilePath("/Users/dmitriy/data/TEMPERATURE_NOVOSIB.sqlite");
    par.parse();

    par.setFilePath("/Users/dmitriy/data/PRICES_NATURAL_GAS_USD.sqlite");
    par.parse();

    par.setFilePath("/Users/dmitriy/data/NORDPOOL_PRICES.sqlite");
    par.parse();

    par.setFilePath("/Users/dmitriy/data/HUMIDITY_MOSCOW.sqlite");
    par.parse();
}
