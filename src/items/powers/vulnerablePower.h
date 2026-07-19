#ifndef VULNERABLEPOWER_H
#define VULNERABLEPOWER_H

#include "abstractpower.h"

class vulnerablePower : public abstractPower
{
    Q_OBJECT
public:
    vulnerablePower(abstractEntity* owner_init, int x);
    void modify_incoming_damage(damageInfo&) override;
    void at_turn_end(game_action&) override;
    QString generate_description() override;
    powerID get_id() override { return powerID::vulnerable; }
};

#endif // VULNERABLEPOWER_H
