#ifndef DATAEXTRACT_H
#define DATAEXTRACT_H

#include <QDateTime>
#include <QString>
#include <QList>

class IDataExtracter {
public:
    virtual ~IDataExtracter() = default;

    virtual QDateTime extract(const QString& raw) = 0;
};



class GraphDataExtracter : public IDataExtracter {
public:
    static const QList<QString> DATA_FORMAT; //TODO: разделить на 2 части где первая будет с часами, а вторая без,
// и если получилось преобразовать ко времени с часами ретурн если нет тогда преобразовывать к гоодам
    // а дальше числа к часам
public:
    ~GraphDataExtracter() override = default;

    QDateTime extract(const QString& raw) override {
        return {};
    }
};

#endif // DATAEXTRACT_H
