#include <iostream>

#include "SqlLiteParser.h"

int main(int argc, char *argv[]) {
    SqlLiteParser par;

    par.setFilePath("/Users/dmitriy/Downloads/BLOOD_SUGAR.sqlite");
    par.parse();
}
