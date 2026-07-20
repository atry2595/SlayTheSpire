#ifndef FEELNOPAINPOWER_H
#define FEELNOPAINPOWER_H

#include "abstractpower.h"

class feelNoPainPower : public abstractPower
{
    Q_OBJECT
private:
    QMetaObject::Connection exhaust_card_connection;

public:
    feelNoPainPower(abstractEntity* owner_init, int x);
    void added_time(game_action&) override;
    QString generate_description() override;
    powerID get_id() override { return powerID::feel_no_pain; }
    QString get_story() override;
};

#endif // FEELNOPAINPOWER_H
