#ifndef DEMONFORMPOWER_H
#define DEMONFORMPOWER_H

#include "abstractpower.h"

class demonFormPower : public abstractPower
{
    Q_OBJECT
public:
    demonFormPower(abstractEntity* owner_init, int x);
    void at_turn_start(game_action&) override;
    QString generate_description() override;
    powerID get_id() override { return powerID::demon_form; }
};

#endif // DEMONFORMPOWER_H
