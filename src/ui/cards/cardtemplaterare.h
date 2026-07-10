#ifndef CARDTEMPLATEUNRARE_H
#define CARDTEMPLATEUNRARE_H

#include "ui/textitem.h"
#include "ui/imageitem.h"
#include "ui/cards/cardparent.h"
#include "cards/abstractcard.h"
#include "categories/cards.h"
#include <QObject>

class CardTemplateRare : public QObject
{
    Q_OBJECT

private:
    abstractCard* card_source = nullptr;

    QPointF card_pos;
    QSizeF card_size = {200, 300};
    QFont base_font;
    QColor base_color = Qt::white;

    qreal zValue;
    qreal z_value_zone = 399;


    CardParent* card_parent = nullptr;
    ImageItem* card_frame = nullptr;
    ImageItem* card_image = nullptr;
    TextItem* card_category = nullptr;
    TextItem* card_name = nullptr;
    TextItem* card_cost = nullptr;
    TextItem* card_description = nullptr;


    void updateCard();
    void reverseCard();

public:
    CardTemplateRare(abstractCard* source, QPointF pos, QSizeF size, qreal zValue);

    // Card Size
    void setCardpos(QPointF value) { card_pos = value; }
    void setCardpos(qreal w, qreal h) { card_pos = QPointF(w, h); }
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
};

#endif // CARDTEMPLATEUNRARE_H
