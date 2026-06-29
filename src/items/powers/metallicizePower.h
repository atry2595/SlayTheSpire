#ifndef METALLICIZEPOWER_H
#define METALLICIZEPOWER_H

#include "abstractpower.h"

class metallicizePower : public abstractPower
{
    Q_OBJECT
public:
    metallicizePower(abstractEntity* owner_init, int x);
    void at_turn_end(game_action&) override;
    QString generate_description() override;
};

#endif // METALLICIZEPOWER_H
