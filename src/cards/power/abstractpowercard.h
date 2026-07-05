#ifndef ABSTRACTPOWERCARD_H
#define ABSTRACTPOWERCARD_H


#include "cards/abstractcard.h"

class abstractPowerCard : public abstractCard
{
    Q_OBJECT

protected:

    // sound effect + damage effect

    // sound effect + damage effect

public:

    abstractPowerCard(QString name_init, QString description_init, int energy_init,
                    bool exhaust_init = false, bool retain_init = false, bool  ethereal_init = false, bool initial_init = false);

    ~abstractPowerCard() = default;

    CardType get_card_type() override final { return CardType::power; }

    virtual QString generate_description() = 0;

};

#endif // ABSTRACTPOWERCARD_H
