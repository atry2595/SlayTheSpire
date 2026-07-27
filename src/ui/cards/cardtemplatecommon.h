#ifndef CARDTEMPLATECOMMON_H
#define CARDTEMPLATECOMMON_H

#include "ui/cards/abstractcardtemplate.h"

class CardTemplateCommon : public abstractCardTemplate
{
    Q_OBJECT

public:
    CardTemplateCommon(combatEvent* eve, abstractCard* source, QPointF pos, QSizeF size, qreal zValue);

    void updateCard() override;
};

#endif // CARDTEMPLATECOMMON_H
