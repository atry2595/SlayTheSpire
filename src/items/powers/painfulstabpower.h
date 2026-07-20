#ifndef PAINFULSTABPOWER_H
#define PAINFULSTABPOWER_H

#include "abstractpower.h"

class painfulStabPower : public abstractPower
{
    Q_OBJECT

private:
    QMetaObject::Connection add_card_connection;

public:
    painfulStabPower(abstractEntity* owner_init, int x);
    void added_time(game_action&) override;
    QString generate_description() override;
    powerID get_id() override { return powerID::painful_stabs; }
    QString get_story() override;
};

#endif // PAINFULSTABPOWER_H
