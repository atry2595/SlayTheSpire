#ifndef BARRICADEPOWER_H
#define BARRICADEPOWER_H

#include "abstractpower.h"

class barricadePower : public abstractPower
{
    Q_OBJECT
public:
    barricadePower(abstractEntity* owner_init, int x);
    void added_time() override;
    QString generate_description() override;
    powerID get_id() override { return powerID::barricade; }
};

#endif // BARRICADEPOWER_H
