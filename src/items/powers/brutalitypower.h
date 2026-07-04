#ifndef BRUTALITYPOWER_H
#define BRUTALITYPOWER_H

#include "abstractpower.h"

class brutalityPower : public abstractPower
{
    Q_OBJECT
private:
    QMetaObject::Connection play_card_connection;

public:
    brutalityPower(abstractEntity* owner_init, int x);
    void at_turn_start(game_action&) override;
    QString generate_description() override;
    powerID get_id() override { return powerID::brutality; }
};

#endif // BRUTALITYPOWER_H
