#include "graphwidget.h"
#include <QPainter>

GraphWidget::GraphWidget(QWidget *parent) : QWidget(parent) {}

void GraphWidget::setData(const QVector<QPointF> &newData) {
    data = newData;
    update();
}

void GraphWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (data.isEmpty()) {
        return;
    }

    int width = this->width();
    int height = this->height();

    double minX = data.first().x();
    double maxX = data.last().x();
    double minY = data.first().y();
    double maxY = data.first().y();
    for (const QPointF &point : data) {
        if (point.y() < minY) minY = point.y();
        if (point.y() > maxY) maxY = point.y();
    }

    // Построение графика.
    for (int i = 1; i < data.size(); ++i) {
        double x1 = (data[i - 1].x() - minX) / (maxX - minX) * width;
        double y1 = height - (data[i - 1].y() - minY) / (maxY - minY) * height;
        double x2 = (data[i].x() - minX) / (maxX - minX) * width;
        double y2 = height - (data[i].y() - minY) / (maxY - minY) * height;
        painter.drawLine(QPointF(x1, y1), QPointF(x2, y2));
    }
}
