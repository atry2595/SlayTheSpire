#ifndef CARDTEMPLATEUNRARE_H
#define CARDTEMPLATEUNRARE_H

#include "abstractcardtemplate.h"

class CardTemplateRare : public abstractCardTemplate
{
    Q_OBJECT

public:
    CardTemplateRare(abstractCard* source, QPointF pos, QSizeF size, qreal zValue);

    void updateCard();
};

#endif // CARDTEMPLATEUNRARE_H
