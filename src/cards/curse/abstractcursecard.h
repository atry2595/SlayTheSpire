#ifndef ABSTRACTCURSECARD_H
#define ABSTRACTCURSECARD_H


#include "cards/abstractcard.h"

class abstractCurseCard : public abstractCard
{
    Q_OBJECT

protected:

    // sound effect + damage effect

    // sound effect + damage effect

public:

    abstractCurseCard(QString name_init, QString description_init, int energy_init,
                       bool exhaust_init, bool retain_init, bool  ethereal_init, bool initial_init);

    ~abstractCurseCard() = default;

    CardType get_card_type() override final { return CardType::curse; }

    virtual QString generate_description() = 0;

};

#endif // ABSTRACTCURSECARD_H
