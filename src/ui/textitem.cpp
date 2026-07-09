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

    rendered_text = QPixmap(size().toSize());

    rendered_text.fill(Qt::red);

    QPainter painter(&rendered_text);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    painter.setFont(font);
    painter.setPen(color);

    painter.drawText(
        rendered_text.rect(),
        alignment,
        text
        );

    painter.end();
}

void TextItem::paint(QPainter* painter,
           const QStyleOptionGraphicsItem* option,
                     QWidget* widget) {
    painter->drawPixmap(
        boundingRect().toRect(),
        rendered_text);
}