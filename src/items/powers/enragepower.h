#ifndef ENRAGEPOWER_H
#define ENRAGEPOWER_H

#include "abstractpower.h"

class enragePower : public abstractPower
{
    Q_OBJECT
private:
    QMetaObject::Connection play_card_connection;

public:
    enragePower(abstractEntity* owner_init, int x);
    void added_time(game_action&) override;
    QString generate_description() override;
    powerID get_id() override { return powerID::enrage; }
};

#endif // ENRAGEPOWER_H
