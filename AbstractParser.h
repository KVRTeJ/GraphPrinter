#ifndef ABSTRACTPARSER_H
#define ABSTRACTPARSER_H

#include <QVector>
#include <QDateTime>

#include "IParser.h"
#include "DataExtract.h"

struct Data {
    QDateTime xAxis {};
    double yAxis {};
};

class AbstractParser : public IParser<QVector<Data>> {
public:
    AbstractParser(const QString& filePath = "") : _filePath(filePath)
    {}
    ~AbstractParser() override = default;

    QString getFilePath() const override {return _filePath;}
    void setFilePath(const QString& filePath) override {_filePath = filePath;}

    IDataExtracter* getDataExtracter() const {return _dataExtracter;}
    void setDataExtracter(IDataExtracter* extracter) {_dataExtracter = extracter;}

    QVector<Data> getData() const override {return _data;}

protected:
    QVector<Data> _data {};

private:
    QString _filePath {""};
    IDataExtracter* _dataExtracter {nullptr};
};

#endif // ABSTRACTPARSER_H
