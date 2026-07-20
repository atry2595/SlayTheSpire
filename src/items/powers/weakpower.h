#ifndef WEAKPOWER_H
#define WEAKPOWER_H

#include "abstractpower.h"

class weakPower : public abstractPower
{
    Q_OBJECT
public:
    weakPower(abstractEntity* owner_init, int x);
    void modify_attack(attackInfo&) override;
    void at_turn_end(game_action&) override;
    QString generate_description() override;
    powerID get_id() override { return powerID::weak; }
    QString get_story() override;
};

#endif // WEAKPOWER_H
