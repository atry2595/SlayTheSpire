#include "imageitem.h"
#include <QPainter>

ImageItem::ImageItem(QGraphicsItem* parent, QSizeF home_size, QPointF home_pos)
    :BaseItem(parent, home_size, home_pos)
{
    setAcceptedMouseButtons(Qt::NoButton);
    setAcceptHoverEvents(false);
}


void ImageItem::setPixmap(const QPixmap& pix) {
    if (pix.cacheKey() == pixmap.cacheKey()) return;
    pixmap = pix;
    has_pixmap = true;
    update();
}

void ImageItem::clearPixmap()  {
    has_pixmap = false;
    pixmap = QPixmap();
    update();
}

void ImageItem::setHighlight(bool b) {
    has_highlight = b;
    update();
}

void ImageItem::paint(QPainter* painter,
           const QStyleOptionGraphicsItem* option,
                      QWidget* widget) {
    if (has_pixmap){

        painter->setPen(Qt::NoPen);
        painter->drawPixmap(boundingRect().toRect(), pixmap);

        if (has_highlight){
            QPen p;
            p.setColor(highlight_color);
            p.setWidth(6);
            painter->setPen(p);
            painter->setBrush(Qt::NoBrush);
            painter->drawRoundedRect(boundingRect(), 8, 8);
        }
    }
    else {
        BaseItem::paint(painter, option, widget);
    }
}