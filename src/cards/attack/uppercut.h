#ifndef UPPERCUT_H
#define UPPERCUT_H
#include <QObject>
#include "abstractattackcard.h"

class uppercut : public abstractAttackCard
{
    Q_OBJECT

protected:

    int base_effect_v = 1;
    int effect_v = 1;
    int base_effect_w = 1;
    int effect_w = 1;

public:

    uppercut();
    ~uppercut() = default;

    void combat_reset() override;

    int get_effect_v() { return effect_v; }

    int get_effect_w() { return effect_w; }

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::uppercut; }
    bool is_rare() override { return false; }

    TargetType get_target_type() override { return TargetType::single_target; }
};

#endif // UPPERCUT_H
