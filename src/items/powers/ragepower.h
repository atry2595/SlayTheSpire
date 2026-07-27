#ifndef RAGEPOWER_H
#define RAGEPOWER_H

#include "abstractpower.h"

class ragePower : public abstractPower
{
    Q_OBJECT
private:
    QMetaObject::Connection play_card_connection;

public:
    ragePower(abstractEntity* owner_init, int x);
    void added_time(game_action&) override;
    void at_turn_end(game_action&) override;
    QString generate_description() override;
    powerID get_id() override { return powerID::rage; }
    QString get_story() override;
};

#endif // RAGEPOWER_H
