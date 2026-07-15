#ifndef CARDTEMPLATELEGEND_H
#define CARDTEMPLATELEGEND_H

#include "abstractcardtemplate.h"

class CardTemplateLegend : public abstractCardTemplate
{
    Q_OBJECT




public:
    CardTemplateLegend(abstractCard* source, QPointF pos, QSizeF size, qreal zValue);

    void updateCard() override;
};

#endif // CARDTEMPLATELEGEND_H
