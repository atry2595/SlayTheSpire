#ifndef STRENGTHPOWER_H
#define STRENGTHPOWER_H

#include "abstractpower.h"

class strengthPower : public abstractPower
{
    Q_OBJECT
public:
    strengthPower(abstractEntity* owner_init, int x);
    void modify_attack(attackInfo&) override;
    QString generate_description() override;
    powerID get_id() override { return powerID::strength; }
};

#endif // STRENGTHPOWER_H
