#ifndef CLASH_H
#define CLASH_H

#include "abstractattackcard.h"

class clash : public abstractAttackCard
{
    Q_OBJECT

public:

    clash();
    ~clash() = default;

    void combat_reset() override;

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;
    void damage_applied() override;
    void update(playInfo& info) override;

    cardID get_card_id() override { return cardID::clash; }
    bool is_rare() override { return false; }
    TargetType get_target_type() override { return TargetType::single_target; }
    bool is_strike() override { return true; }
};

#endif // CLASH_H
