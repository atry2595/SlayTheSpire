#include "abstractcardtemplate.h"

abstractCardTemplate::abstractCardTemplate(abstractCard* source, QPointF pos, QSizeF size, qreal z_value)
    :card_source(source),
    card_pos(pos),
    card_size(size),
    zValue(z_value)
{
    card_parent = new CardParent(nullptr, card_size, card_pos, z_value_zone);
}



void abstractCardTemplate::setCardpos(QPointF value) {
    card_pos = value;
    card_parent->setHomePos(card_pos);
}