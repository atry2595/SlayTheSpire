#ifndef BASEITEM_H
#define BASEITEM_H

#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>
#include <QPropertyAnimation>
#include <QEasingCurve>

class BaseItem : public QGraphicsObject
{
    Q_OBJECT

    Q_PROPERTY(QSizeF size READ size WRITE setSize)
    Q_PROPERTY(QRectF geometry READ geometry WRITE setGeometry)
    bool f = false;
    bool l = true;

public:
    explicit BaseItem(QGraphicsItem* parent = nullptr, QSizeF home_size = {0, 0}, QPointF home_pos = {0, 0});

    QRectF boundingRect() const override;

    void paint(QPainter* painter,
               const QStyleOptionGraphicsItem* option,
               QWidget* widget) override;


    void setMovable() {f = true;}
protected:
    // Mouse
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

protected:
    // Current State
    QSizeF m_size;

    // Home State
    QPointF home_pos;
    QSizeF home_size;
    qreal home_rotation = 0.0;
    qreal home_scale = 1.0;
    qreal home_opacity = 1.0;
    qreal home_z = 0.0;

public:
    // Current Property
    QSizeF size() const { return m_size; }
    void setSize(QSizeF size);
    void setSize(qreal w, qreal h) { setSize(QSizeF(w,h)); }

    QRectF geometry() const { return QRectF(pos(), size()); }
    void setGeometry(QRectF rect) { setPos(rect.x(), rect.y()); setSize(rect.width(), rect.height()); }
    void setGeometry(QPointF pos, QSizeF size) {setGeometry({pos, size}); }
    void setGeometry(qreal x, qreal y, qreal w, qreal h) { setGeometry({x, y, w, h}); }

    QPointF center() const { return (pos() + QPointF(m_size.width()/2, m_size.height()/2) ); }

    // Home State
    void saveHomeState();
    void returnToHome(int duration = 250);

    void setHomePos(QPointF p) { home_pos = p;}
    QPointF homePos() const { return home_pos; }

    void setHomeSize(QSizeF s) { home_size = s; }
    QSizeF homeSize() const {return home_size; }

    void setHomeRotation(qreal r) { home_rotation = r; }
    qreal homeRotation() const { return home_rotation; }

    void setHomeScale(qreal s) { home_scale = s; }
    qreal homeScale() const { return home_scale; }

    void setHomeOpacity(qreal o) { home_opacity = o;}
    qreal homeOpacity() const { return home_opacity; }

    void setHomeZ(qreal z) { home_z = z;}
    qreal homeZ() const { return home_z; }

    // Animation Factory
    QPropertyAnimation* createMoveAnimation(
        QPointF target,
        int duration = 250,
        QEasingCurve easing = QEasingCurve::Linear);

    QPropertyAnimation* createRotateAnimation(
        qreal target,
        int duration = 250,
        QEasingCurve easing = QEasingCurve::Linear);

    QPropertyAnimation* createScaleAnimation(
        qreal target,
        int duration = 250,
        QEasingCurve easing = QEasingCurve::Linear);

    QPropertyAnimation* createOpacityAnimation(
        qreal target,
        int duration = 250,
        QEasingCurve easing = QEasingCurve::Linear);

    QPropertyAnimation* createResizeAnimation(
        QSizeF target,
        int duration = 250,
        QEasingCurve easing = QEasingCurve::Linear);

    QPropertyAnimation* createGeometryAnimation(
        QRectF target,
        int duration = 250,
        QEasingCurve easing = QEasingCurve::Linear);

    // Quick Animation
    void moveTo(QPointF target,
                int duration = 250,
                QEasingCurve easing = QEasingCurve::Linear);

    void rotateTo(qreal target,
                  int duration = 250,
                  QEasingCurve easing = QEasingCurve::Linear);

    void scaleTo(qreal target,
                 int duration = 250,
                 QEasingCurve easing = QEasingCurve::Linear);

    void fadeTo(qreal target,
                int duration = 250,
                QEasingCurve easing = QEasingCurve::Linear);

    void resizeTo(QSizeF target,
                  int duration = 250,
                  QEasingCurve easing = QEasingCurve::Linear);

    void geometryTo(QRectF target,
                    int duration = 250,
                    QEasingCurve easing = QEasingCurve::Linear);
};

#endif