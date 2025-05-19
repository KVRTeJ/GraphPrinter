#include <iostream>

#include "SqlLiteParser.h"

int main(int argc, char *argv[]) {
    SqlLiteParser par;

    par.setFilePath("/Users/dmitriy/Downloads/BLOOD_SUGAR.sqlite");
    par.parse();

    // par.setFilePath("/Users/dmitriy/Downloads/TEMPERATURE_NOVOSIB.sqlite");
    // par.parse();

    // par.setFilePath("/Users/dmitriy/Downloads/PRICES_NATURAL_GAS_USD.sqlite");
    // par.parse();

    // par.setFilePath("/Users/dmitriy/Downloads/NORDPOOL_PRICES.sqlite");
    // par.parse();
}
