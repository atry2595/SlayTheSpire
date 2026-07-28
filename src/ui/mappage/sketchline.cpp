#include "sketchline.h"
#include "utils/RNG.h"

SketchLine::SketchLine(QPointF start,
                       QPointF end,
                       QGraphicsItem *parent)
    : QGraphicsObject(parent),
    p1(start),
    p2(end)
{
    generateSketch();
}

void SketchLine::setPoints(QPointF start, QPointF end)
{
    prepareGeometryChange();

    p1 = start;
    p2 = end;

    generateSketch();

    update();
}

QRectF SketchLine::boundingRect() const
{
    QRectF r(p1, p2);
    r = r.normalized();
    r.adjust(-10,-10,10,10);
    return r;
}

void SketchLine::generateSketch()
{
    points.clear();

    double totalLen = QLineF(p1, p2).length();

    int segments = std::max(8, int(totalLen / 12.0));

    QPointF dir = p2 - p1;

    QPointF normal(-dir.y(), dir.x());

    double len = std::hypot(normal.x(), normal.y());

    if(len != 0)
        normal /= len;

    for(int i=0;i<=segments;i++)
    {
        double t = double(i)/segments;

        QPointF p = p1 + dir*t;

        double noise =
            RNG::instance().random(-2.5,2.5);

        p += normal*noise;

        points.push_back(p);
    }
}

void SketchLine::paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *,
                       QWidget *)
{
    painter->setRenderHint(QPainter::Antialiasing,true);

    QPen pen(Qt::black);

    pen.setWidth(3);

    pen.setCapStyle(Qt::RoundCap);

    pen.setJoinStyle(Qt::RoundJoin);

    pen.setDashPattern({8,6});

    painter->setPen(pen);

    constexpr qreal desiredDash = 50;

    for (int i = 0; i < points.size() - 1; ++i)
    {
        QLineF seg(points[i], points[i + 1]);

        qreal len = seg.length();

        if (len < 1.0)
            continue;

        int dashCount = std::max(1, int(len / (desiredDash * 4)));

        qreal unit = len / (dashCount * 1.9);

        for (int j = 0; j < dashCount; ++j)
        {
            qreal s = j * unit * 2.0;
            qreal e = s + unit;

            painter->drawLine(
                seg.pointAt(s / len),
                seg.pointAt(e / len)
                );
        }
    }
}