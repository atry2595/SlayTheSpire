#ifndef BLOOD_FOR_BLOOD_H
#define BLOOD_FOR_BLOOD_H

#include "abstractattackcard.h"

class blood_for_blood : public abstractAttackCard
{
    Q_OBJECT


public:

    blood_for_blood();
    ~blood_for_blood() = default;

    void combat_reset() override;

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;
    void damage_applied() override;

    cardID get_card_id() override { return cardID::blood_for_blood; }
    bool is_rare() override { return false; }
    TargetType get_target_type() override { return TargetType::single_target; }
};

#endif // BLOOD_FOR_BLOOD_H
