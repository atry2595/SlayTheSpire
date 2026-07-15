#ifndef CARDTEMPLATEUNCOMMON_H
#define CARDTEMPLATEUNCOMMON_H

#include "abstractcardtemplate.h"


class CardTemplateUncommon : public abstractCardTemplate
{
    Q_OBJECT

public:
    CardTemplateUncommon(combatEvent* eve, abstractCard* source, QPointF pos, QSizeF size, qreal zValue);

    void updateCard();
};

#endif // CARDTEMPLATEUNCOMMON_H
