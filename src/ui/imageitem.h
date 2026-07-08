#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include "baseitem.h"

class ImageItem : public BaseItem
{
    Q_OBJECT

protected:
    QPixmap pixmap;
    bool has_pixmap = false;
public:
    ImageItem(QGraphicsItem* parent = nullptr, QSizeF home_size = {0, 0}, QPointF home_pos = {0, 0});
    void setPixmap(const QPixmap& pix);

    void clearPixmap();

    const QPixmap& getPixmap() const { return pixmap; }

    bool hasPixmap() const { return has_pixmap; }

    void paint(QPainter* painter,
               const QStyleOptionGraphicsItem* option,
               QWidget* widget) override;
};

#endif // IMAGEITEM_H
