#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>

#include "JsonParser.h"

JsonParser::JsonParser(const QString& filePath)
    : AbstractParser(filePath)
{}

bool JsonParser::parse() {
    //TODO: if !dataExtracter

    QFile file(getFilePath());

    if (!file.open(QIODevice::ReadOnly)) {
        assert(false);
        return false;
    }

    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll(), &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << parseError.errorString();
        assert(false);
        return false;
    }

    if (!jsonDoc.isArray()) {
        assert(false); //Root is not an array
        return false;
    }

    QList<GraphData> parsed;

    QJsonArray rootArray = jsonDoc.array();
    for (auto it = rootArray.begin(); it != rootArray.end(); ++it) {
        if (!it->isArray()) {
            assert(false); //Invalid entry format - expected array
            continue;
        }

        QJsonArray innerArray = it->toArray();
        if (innerArray.size() != 2) {
            assert(false); //Invalid entry size - expected 2 elements
            continue;
        }

        QDateTime data = getDataExtracter()->extract(innerArray[0].toString());
        if(!data.isValid()) {
            assert(false); //TODO: и это
        }
        if(!innerArray[1].isDouble()) {
            assert(false); //Not double
        }
        double value = innerArray[1].toDouble();

        parsed.push_back({data,
                          value});
    }

    _data = QVector<GraphData>(parsed.size());
    int i = 0;
    for(auto it = parsed.begin(); it != parsed.end(); ++it, ++i) {
        _data[i] = *it;
    }

    return false;
}
