#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <QVector>
#include <QPointF>

class GraphWidget : public QWidget {
    Q_OBJECT

public:
    explicit GraphWidget(QWidget *parent = nullptr);
    void setData(const QVector<QPointF> &newData);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<QPointF> data;
};

#endif // GRAPHWIDGET_H
