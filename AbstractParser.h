#ifndef ABSTRACTPARSER_H
#define ABSTRACTPARSER_H

#include <QVector>
#include <QDateTime>

#include "IParser.h"

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

    QVector<Data> getData() const override {return _data;}

protected:
    QVector<Data> _data {};

private:
    QString _filePath {""};
};

#endif // ABSTRACTPARSER_H
