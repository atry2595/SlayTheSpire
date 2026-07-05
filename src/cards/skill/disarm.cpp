#include "disarm.h"
#include "categories/powers.h"
#include "items/powers/powerfactory.h"

disarm::disarm()
    :abstractSkillCard(tr("Disarm"), "", 1, true, false, false, false)
{
    QString s;
    s += tr("Enemy loses %1 Strength.").arg(effect);
    if (is_exhaust) s+= tr("\nExhaust.");
    base_description = description = s;
}

QString disarm::generate_description(){

    QString s;
    s += tr("Enemy loses %1 Strength.").arg(effect);
    if (is_exhaust) s+= tr("\nExhaust.");
    return s;
}

void disarm::play(playInfo& play_info){
    for (auto item : play_info.target_list){
        abstractPower* p = PowerFactory::createPower(powerID::strength, item, -effect);
        item->add_power(play_info.actions, p);
    }
}

void disarm::upgrade(){
    effect = 3;
    is_upgraded = true;
    description = generate_description();
}

void disarm::base_upgrade(){
    base_effect = effect = 3;
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}





