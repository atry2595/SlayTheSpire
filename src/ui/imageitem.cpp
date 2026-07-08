#include "imageitem.h"
#include <QPainter>

ImageItem::ImageItem(QGraphicsItem* parent, QSizeF home_size, QPointF home_pos)
    :BaseItem(parent, home_size, home_pos)
{}


void ImageItem::setPixmap(const QPixmap& pix) {
    pixmap = pix;
    has_pixmap = true;
    update();
}

void ImageItem::clearPixmap()  {
    has_pixmap = false;
    pixmap = QPixmap();
    update();
}

void ImageItem::paint(QPainter* painter,
           const QStyleOptionGraphicsItem* option,
                      QWidget* widget) {
    if (has_pixmap){
        painter->drawPixmap(boundingRect().toRect(), pixmap);
    }
    else {
        BaseItem::paint(painter, option, widget);
    }
}