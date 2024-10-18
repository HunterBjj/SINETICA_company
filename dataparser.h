#ifndef DATAPARSER_H
#define DATAPARSER_H

#include <QString>
#include <QVector>
#include <QPointF>

class DataParser {
public:
    QVector<QPointF> parse(const QString &fileName);

private:
    double calculateLogMag(double real, double imag);
};

#endif // DATAPARSER_H
