#ifndef ABSTRACTCARDTEMPLATE_H
#define ABSTRACTCARDTEMPLATE_H

#include "ui/textitem.h"
#include "ui/imageitem.h"
#include "ui/cards/cardparent.h"
#include "cards/abstractcard.h"
#include "categories/cards.h"
#include <QObject>

class abstractCardTemplate : public QObject
{
    Q_OBJECT

private:
    combatEvent* event;

protected:
    abstractCard* card_source = nullptr;

    QPointF card_pos;
    QSizeF card_size = {200, 300};
    QFont base_font;
    QColor base_color = Qt::white;

    qreal zValue;
    qreal z_value_zone = 399;

    bool locked = false;

    CardParent* card_parent = nullptr;
    ImageItem* card_frame = nullptr;
    ImageItem* card_image = nullptr;
    TextItem* card_category = nullptr;
    TextItem* card_name = nullptr;
    TextItem* card_cost = nullptr;
    TextItem* card_description = nullptr;

public:
    abstractCardTemplate(combatEvent* eve, abstractCard* source, QPointF pos, QSizeF size, qreal zValue);
    ~abstractCardTemplate();

    // Card pos
    void setCardpos(QPointF value);
    void setCardpos(qreal x, qreal y) { setCardpos(QPointF(x, y)); }
    QPointF getCardpos() const { return card_pos; }

    // Card Size
    void setCardSize(QSizeF value) { card_size = value; }
    void setCardSize(qreal w, qreal h) { card_size = QSizeF(w, h); }
    QSizeF getCardSize() const { return card_size; }

    // Base Font
    void setBaseFont(const QFont& value) { base_font = value; }
    const QFont& getBaseFont() const { return base_font; }

    // Base Color
    void setBaseColor(const QColor& value) { base_color = value; }
    const QColor& getBaseColor() const { return base_color; }

    CardParent* getParent() { return card_parent; }


    virtual void updateCard() = 0;
};

#endif // ABSTRACTCARDTEMPLATE_H
