#ifndef ABSTRACTSTATUSCARD_H
#define ABSTRACTSTATUSCARD_H


#include "cards/abstractcard.h"

class abstractStatusCard : public abstractCard
{
    Q_OBJECT

protected:

    // sound effect + damage effect

    // sound effect + damage effect

public:

    abstractStatusCard(QString name_init, QString description_init, int energy_init,
                       bool exhaust_init, bool retain_init, bool  ethereal_init, bool initial_init);

    ~abstractStatusCard() = default;

    CardType get_card_type() override final { return CardType::status; }

    virtual QString generate_description() = 0;

};

#endif // ABSTRACTSTATUSCARD_H
