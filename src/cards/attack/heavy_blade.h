#ifndef HEAVY_BLADE_H
#define HEAVY_BLADE_H

#include "abstractattackcard.h"

class heavy_blade : public abstractAttackCard
{
    Q_OBJECT

protected:
    int base_effect = 3;
    int effect = 3;

public:

    heavy_blade();
    ~heavy_blade() = default;

    void combat_reset() override;

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::heavy_blade; }
    bool is_rare() override { return false; }
    TargetType get_target_type() override { return TargetType::single_target; }
};

#endif // HEAVY_BLADE_H
