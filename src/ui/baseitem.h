#ifndef BASEITEM_H
#define BASEITEM_H

#include <QGraphicsObject>
#include <QPropertyAnimation>
#include <QGraphicsSceneMouseEvent>

class BaseItem : public QGraphicsObject
{
    Q_OBJECT

    QSizeF itemSize;
    QPointF homePos = {600, 400};

public:
    explicit BaseItem(QGraphicsItem* parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter* painter,
               const QStyleOptionGraphicsItem* option,
               QWidget* widget) override;

    void setSize(qreal width, qreal height);

    void moveTo(QPointF point);

    void setHomePos(QPointF p){
        setPos(p);
        homePos = p;
    }

    void setPixmap(const QPixmap& p) {
        pixmap = p;
        hasPixmap = true;
        update();
    }
protected:
    QPropertyAnimation* moveAnim = nullptr;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

    QPixmap pixmap;
    bool hasPixmap = false;

};

#endif // BASEITEM_H
