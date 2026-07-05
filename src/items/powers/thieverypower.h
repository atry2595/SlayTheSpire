#ifndef THIEVERYPOWER_H
#define THIEVERYPOWER_H

#include "abstractpower.h"

class thieveryPower : public abstractPower
{
    Q_OBJECT

private:
    QMetaObject::Connection attack_connection;

public:
    thieveryPower(abstractEntity* owner_init, int x);
    void added_time(game_action&) override;
    QString generate_description() override;
    powerID get_id() override { return powerID::thievery; }
};

#endif // THIEVERYPOWER_H
