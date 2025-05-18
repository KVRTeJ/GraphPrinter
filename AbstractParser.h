#ifndef ABSTRACTPARSER_H
#define ABSTRACTPARSER_H

#include <qvector.h>

#include "IParser"

struct Data {
    double xAxis = 0;
    double yAxis = 0;
};

class AbstractParser : public IParser<QVector<Data>> {
public:

}

#endif // ABSTRACTPARSER_H
