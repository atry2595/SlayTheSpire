#ifndef POMMEL_STRIKE_H
#define POMMEL_STRIKE_H

#include "abstractattackcard.h"

class pommel_strike : public abstractAttackCard
{
    Q_OBJECT

protected:
    int base_count = 1;
    int count = 1;

public:

    pommel_strike();
    ~pommel_strike() = default;

    void combat_reset() override;

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::pommel_strike; }
    bool is_rare() override { return false; }
    TargetType get_target_type() override { return TargetType::single_target; }
    bool is_strike() override { return true; }
};

#endif // POMMEL_STRIKE_H
