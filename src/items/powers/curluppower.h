#ifndef CURLUPPOWER_H
#define CURLUPPOWER_H

#include "abstractpower.h"

class curlUpPower : public abstractPower
{
    Q_OBJECT
public:
    curlUpPower(abstractEntity* owner_init, int x);
    void damage_applied(game_action&) override;
    QString generate_description() override;
    powerID get_id() override { return powerID::curl_up; }
    QString get_story() override;
};

#endif // CURLUPPOWER_H
