#ifndef FRAILPOWER_H
#define FRAILPOWER_H

#include "abstractpower.h"

class frailPower : public abstractPower
{
    Q_OBJECT
public:
    frailPower(abstractEntity* owner_init, int x);
    void modify_blocking(blockingInfo&) override;
    void at_turn_end(game_action&) override;
    QString generate_description() override;

    powerID get_id() override { return powerID::frail; }
    QString get_story() override;
};

#endif // FRAILPOWER_H
