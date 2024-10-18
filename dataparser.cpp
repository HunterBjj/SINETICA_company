#include "dataparser.h"
#include <QFile>
#include <QTextStream>
#include <QtMath>
#include <QRegularExpression>
#include <QMessageBox>


QVector<QPointF> DataParser::parse(const QString& filePath) {
    QVector<QPointF> points;
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(nullptr, "Error", "Unable to open file.");
        return points;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();

        // Пропускаем комментарии и заголовки
        if (line.startsWith("#") || line.startsWith("!")) {
            continue;
        }

        // Разделяем строку на части по пробелам
        QStringList fields = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

        if (fields.size() == 3) {
            bool ok1, ok2, ok3;
            double freq = fields[0].toDouble(&ok1);
            double realPart = fields[1].toDouble(&ok2);
            double imagPart = fields[2].toDouble(&ok3);

            if (ok1 && ok2 && ok3) {
                double magnitude = qSqrt(realPart * realPart + imagPart * imagPart);
                double logMag = 20 * qLn(magnitude) / qLn(10);  // Конвертируем в dB
                points.append(QPointF(freq, logMag));
            } else {
                QMessageBox::warning(nullptr, "Error", "Invalid data in file.");
            }
        }
    }

    file.close();
    return points;
}

double DataParser::calculateLogMag(double real, double imag) {
    double magnitude = qSqrt(real * real + imag * imag);
    return 20 * qLn(magnitude) / qLn(10);
}
