#ifndef RITUALPOWER_H
#define RITUALPOWER_H

#include "abstractpower.h"

class ritualPower : public abstractPower
{
    Q_OBJECT
public:
    ritualPower(abstractEntity* owner_init, int x);
    void at_turn_start(game_action&) override;
    QString generate_description() override;
    powerID get_id() override { return powerID::ritual; }
};

#endif // RITUALPOWER_H
