#include <QtSql>

#include "SqlLiteParser.h"

#include <assert.h>
#include <QDebug>

SqlLiteParser::SqlLiteParser(const QString& filePath)
    : AbstractParser(filePath)
{}

bool SqlLiteParser::parse() {
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

    QSqlQuery query;
    if(!query.exec("SELECT * FROM " + tables.first())) {
        dataBase.close();
        assert(false); //TODO: убрать это
    } else {
        while(query.next()) {
            QString raw = query.value(0).toString();


            auto splitData = raw.split(' ', Qt::SkipEmptyParts);
            // double val = query.value(1).toDouble();
            QDateTime data = QDateTime::fromString(splitData[0], "dd.MM.yyyy");
            data = data.addSecs(splitData[1].toInt() * 60);
            qDebug() << splitData << data;
        }
    }
    dataBase.close();

    return false;
}
