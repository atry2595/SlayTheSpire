#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include "baseitem.h"

class ImageItem : public BaseItem
{
    Q_OBJECT

protected:
    QPixmap pixmap;
    bool has_pixmap = false;
    bool has_highlight = false;
    QColor highlight_color = Qt::yellow;

public:
    ImageItem(QGraphicsItem* parent = nullptr, QSizeF home_size = {0, 0}, QPointF home_pos = {0, 0});

    void setPixmap(const QPixmap& pix);
    const QPixmap& getPixmap() const { return pixmap; }
    void clearPixmap();
    bool hasPixmap() const { return has_pixmap; }

    bool hashighlight() { return has_highlight; }
    bool gethighlight() { return has_highlight; }
    QColor getColorhighlight() { return highlight_color; }

    void setHighlightColor(QColor clr = Qt::yellow) { highlight_color = clr; }
    void setHighlight(bool b = true);

    void paint(QPainter* painter,
               const QStyleOptionGraphicsItem* option,
               QWidget* widget) override;
};

#endif // IMAGEITEM_H
