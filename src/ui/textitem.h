#ifndef TEXTITEM_H
#define TEXTITEM_H

#include "baseitem.h"
#include <QFont>

class TextItem : public BaseItem
{
    Q_OBJECT

private:
    QString text;
    QFont font;
    QColor color;

    Qt::Alignment alignment;

    QPixmap rendered_text;

    void renderText();

public:
    TextItem(QGraphicsItem* parent = nullptr, QSizeF home_size = {0, 0}, QPointF home_pos = {0, 0});

    void setText(const QString& t);
    const QString& getText() const {return text;}

    void setFont(const QFont& t);
    const QFont& getFont() const {return font;}

    void setColor(const QColor& t);
    const QColor& getColor() const {return color;}

    void setAlignment(Qt::Alignment t);
    const Qt::Alignment& getAligment() const {return alignment;}

    const QPixmap& getRendered_text() const {return rendered_text;}

    void paint(QPainter* painter,
               const QStyleOptionGraphicsItem* option,
               QWidget* widget) override;




};

#endif // TEXTITEM_H
