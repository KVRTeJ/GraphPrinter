#ifndef IPARSER_H
#define IPARSER_H

#include <qstring.h>

template<typename DataType>
class IParser {
public:
    virtual ~IParser() = default;

    virtual QString getFilePath() const = 0;
    virtual void setFilePath(const QString& filePath) = 0;

    virtual bool parse() = 0;

    virtual DataType getData() const = 0;
};

#endif // IPARSER_H
