#include "textitem.h"
#include <QPainter>

TextItem::TextItem(QGraphicsItem* parent,
                   QSizeF home_size,
                   QPointF home_pos)
    : BaseItem(parent, home_size, home_pos)
{
    setAcceptedMouseButtons(Qt::NoButton);
    setAcceptHoverEvents(false);

    color = Qt::white;
    alignment = Qt::AlignCenter;

    renderText();
    update();
}

void TextItem::setText(const QString& t)
{
    text = t;
    renderText();
    update();
}

void TextItem::setFont(const QFont& f)
{
    font = f;
    renderText();
    update();
}

void TextItem::setColor(const QColor& c)
{
    color = c;
    renderText();
    update();
}

void TextItem::setAlignment(Qt::Alignment align)
{
    alignment = align;
    renderText();
    update();
}

void TextItem::renderText()
{
    if(size().isEmpty())
        return;

    QSize renderSize = (size() * 10).toSize();

    rendered_text = QPixmap(renderSize);
    rendered_text.fill(Qt::transparent);

    QPainter painter(&rendered_text);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    painter.scale(10,10);


    painter.setFont(font);
    painter.setPen(color);

    QRectF rect(0,0,size().width(),size().height());

    painter.drawText(
        rect,
        alignment | Qt::TextWordWrap,
        text
        );

    painter.end();
}

void TextItem::paint(QPainter* painter,
           const QStyleOptionGraphicsItem* option,
                     QWidget* widget) {
    painter->drawPixmap(
        boundingRect().toRect(),
        rendered_text
        );
}