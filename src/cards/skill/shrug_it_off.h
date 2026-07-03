#ifndef SHRUG_IT_OFF_H
#define SHRUG_IT_OFF_H
#include <QObject>
#include "abstractskillcard.h"

class shrug_it_off : public abstractSkillCard
{
    Q_OBJECT

protected:
    int base_block = 8;
    int block = 8;

public:

    shrug_it_off();
    ~shrug_it_off() = default;

    void combat_reset() override;

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::shrug_it_off; }
    bool is_rare() override { return false; }

    TargetType get_target_type() override { return TargetType::self; }
};

#endif // SHRUG_IT_OFF_H
