#ifndef DEPENDENCYINVERSION_H
#define DEPENDENCYINVERSION_H


#include "IOC_Contaner.h"

#include "IParser.h"
#include "JsonParser.h"
#include "SqlLiteParser.h"

#include "IChartCreator.h"
#include "LineChartCreator.h"
#include "AreaChartCreator.h"
#include "SplineChartCreator.h"
#include "ScatterChartCreator.h"

#include "DataExtract.h"

#include <QObject>
#include <QtCore/qdebug.h>

static IOCContainer gContainer;

class DIConfiguration {
public:
    static void configure() {
        gContainer.RegisterInstance<IParser, JsonParser>();

        gContainer.RegisterInstance<IChartCreator, LineChartCreator>();
    }

    static void switchToJsonParser(IDataExtracter* extracter) {
        gContainer.RegisterInstance<IParser>(std::make_shared<JsonParser>("", extracter));
    }
    static void switchToSqlLiteParser(IDataExtracter* extracter) {
        gContainer.RegisterInstance<IParser>(std::make_shared<SqlLiteParser>("", extracter));
    }

    static void switchToLineChart() {
        gContainer.RegisterInstance<IChartCreator, LineChartCreator>();
        qDebug() << "\tline";
    }
    static void switchToAreaChart() {
        gContainer.RegisterInstance<IChartCreator, AreaChartCreator>();
        qDebug() << "\tarea";
    }

};

#endif // DEPENDENCYINVERSION_H
