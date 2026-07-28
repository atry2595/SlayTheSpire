#include "abstractcardtemplate.h"

abstractCardTemplate::abstractCardTemplate(combatEvent* eve, abstractCard* source, QPointF pos, QSizeF size, qreal z_value)
    :card_source(source),
    card_pos(pos),
    card_size(size),
    zValue(z_value),
    event(eve)
{
    card_parent = new CardParent(eve, nullptr, card_size, card_pos, z_value_zone);
    card_parent->setSource(source);
}

abstractCardTemplate::~abstractCardTemplate() {
    card_parent->deleteLater();
}


void abstractCardTemplate::setCardpos(QPointF value) {
    card_pos = value;
    card_parent->setHomePos(card_pos);
}