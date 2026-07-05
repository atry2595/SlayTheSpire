#ifndef ENTANGLEDPOWER_H
#define ENTANGLEDPOWER_H

#include "abstractpower.h"

class entangledPower : public abstractPower
{
    Q_OBJECT

private:
    QMetaObject::Connection add_card_connection;

public:
    entangledPower(abstractEntity* owner_init, int x);
    void added_time(game_action&) override;
    void at_turn_end(game_action&) override;
    QString generate_description() override;
    powerID get_id() override { return powerID::entangled; }
};

#endif // ENTANGLEDPOWER_H
