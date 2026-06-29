#ifndef VULNERABLEPOWER_H
#define VULNERABLEPOWER_H

#include "abstractpower.h"

class vulnerablePower : public abstractPower
{
    Q_OBJECT
public:
    vulnerablePower(abstractEntity* owner_init, int x);
    void modify_incoming_damage(damageInfo&) override;
    QString generate_description() override;
};

#endif // VULNERABLEPOWER_H
