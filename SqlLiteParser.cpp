#include <QtSql>

#include "SqlLiteParser.h"

#include <assert.h>
#include <QDebug>

SqlLiteParser::SqlLiteParser(const QString& filePath)
    : AbstractParser(filePath)
{}

bool SqlLiteParser::parse() {
    //TODO: if !dataExtracter

    QSqlDatabase dataBase = QSqlDatabase::addDatabase("QSQLITE");

    dataBase.setDatabaseName(getFilePath());
    if(!dataBase.open()) {
        assert(false); //TODO: убрать это
    }

    auto tables = dataBase.tables();
    if(tables.isEmpty()) {
        dataBase.close();
        assert(false); //TODO: убрать это
    }

    QList<GraphData> parsed;

    QSqlQuery query;
    if(!query.exec("SELECT * FROM " + tables.first())) {
        dataBase.close();
        assert(false); //TODO: убрать это
    } else {
        while(query.next()) {
            QString rawData = query.value(0).toString();
            QDateTime data = getDataExtracter()->extract(rawData);
            if(!data.isValid()) {
                assert(false); //TODO: и это
            }
            bool ok;
            double value = query.value(1).toDouble(&ok);
            if(!ok) {
                assert(false); //TODO: и это
            }

            parsed.push_back({data,
                              value});
        }
    }
    dataBase.close();

    _data = QVector<GraphData>(parsed.size());
    int i = 0;
    for(auto it = parsed.begin(); it != parsed.end(); ++it, ++i) {
        _data[i] = *it;
    }

    return false;
}
