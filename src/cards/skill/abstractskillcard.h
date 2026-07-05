#ifndef ABSTRACTSKILLCARD_H
#define ABSTRACTSKILLCARD_H


#include "cards/abstractcard.h"

class abstractSkillCard : public abstractCard
{
    Q_OBJECT

protected:

    // sound effect + damage effect

    // sound effect + damage effect

public:

    abstractSkillCard(QString name_init, QString description_init, int energy_init,
                       bool exhaust_init, bool retain_init, bool  ethereal_init, bool initial_init);

    ~abstractSkillCard() = default;

    CardType get_card_type() override final { return CardType::skill; }

    virtual QString generate_description() = 0;

};

#endif // ABSTRACTSKILLCARD_H
