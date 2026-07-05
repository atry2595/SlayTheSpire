#ifndef POWER_THROUGH_H
#define POWER_THROUGH_H
#include <QObject>
#include "abstractskillcard.h"

class power_through : public abstractSkillCard
{
    Q_OBJECT

protected:
    int base_block = 15;
    int block = 15;

public:

    power_through();
    ~power_through() = default;

    void combat_reset() override;

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::power_through; }
    bool is_rare() override { return false; }

    TargetType get_target_type() override { return TargetType::self; }
};

#endif // POWER_THROUGH_H
