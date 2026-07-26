#pragma once

#include <QGraphicsObject>
#include <QPainter>
#include <QRandomGenerator>

class SketchLine : public QGraphicsObject
{
    Q_OBJECT

public:
    SketchLine(QPointF start,
               QPointF end,
               QGraphicsItem* parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter* painter,
               const QStyleOptionGraphicsItem*,
               QWidget*) override;

    void setPoints(QPointF start, QPointF end);

private:
    QPointF p1;
    QPointF p2;

    QVector<QPointF> points;

    void generateSketch();
};