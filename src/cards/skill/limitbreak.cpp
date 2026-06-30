#include "limitbreak.h"
#include "categories/powers.h"
#include "items/powers/powerfactory.h"

limit_break::limit_break()
    :abstractSkillCard(tr("Limit break"), "", 1, true, false, false, false)
{
    QString s;
    s += tr("Double your Strength.");
    if (is_exhaust) s+= tr("\nExhaust.");
    base_description = description = s;
}

QString limit_break::generate_description(){

    QString s;
    s += tr("Double your Strength.");
    if (is_exhaust) s+= tr("\nExhaust.");
    return s;
}

void limit_break::play(playInfo& play_info){
    abstractPower* power = play_info.attacker->get_spec_power(powerID::strength);
    if (power) play_info.attacker->add_power(power);
}

void limit_break::upgrade(){
    is_exhaust = false;
    is_upgraded = true;
    description = generate_description();
}

void limit_break::base_upgrade(){
    base_is_exhaust = is_exhaust = false;
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}





