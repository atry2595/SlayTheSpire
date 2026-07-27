#ifndef BERSERKPOWER_H
#define BERSERKPOWER_H

#include "abstractpower.h"

class berserkPower : public abstractPower
{
    Q_OBJECT

public:
    berserkPower(abstractEntity* owner_init, int x);
    void at_turn_start(game_action&) override;
    QString generate_description() override;
    powerID get_id() override { return powerID::berserk; }
    QString get_story() override;
};

#endif // BERSERKPOWER_H
