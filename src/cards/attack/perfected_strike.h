#ifndef PERFECTED_STRIKE_H
#define PERFECTED_STRIKE_H

#include "abstractattackcard.h"

class perfected_strike : public abstractAttackCard
{
    Q_OBJECT

protected:
    int base_addit_dmg = 2;
    int addit_dmg = 2;

public:

    perfected_strike();
    ~perfected_strike() = default;

    void combat_reset() override;

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;
    void damage_applied() override;

    cardID get_card_id() override { return cardID::perfected_strike; }
    bool is_rare() override { return false; }
    TargetType get_target_type() override { return TargetType::single_target; }
    bool is_strike() override { return true; }
};

#endif // PERFECTED_STRIKE_H
