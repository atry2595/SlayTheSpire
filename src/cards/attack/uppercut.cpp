#include "uppercut.h"
#include "categories/powers.h"
#include "items/powers/powerfactory.h"

uppercut::uppercut()
    :abstractAttackCard(tr("uppercut"), "", 2, 13, false, false, false, false)
{
    QString s;
    s += tr("Deal %1 damage.").arg(damage);
    s += tr("\nApply %1 Weak.").arg(effect_w);
    s += tr("\nApply %1 Vulnerable.").arg(effect_v);
    base_description = description = s;
}

QString uppercut::generate_description(){

    QString s;
    s += tr("Deal %1 damage.").arg(damage);
    s += tr("\nApply %1 Weak.").arg(effect_w);
    s += tr("\nApply %1 Vulnerable.").arg(effect_v);
    return s;
}

void uppercut::play(playInfo& play_info){
    perform_attack(play_info.attacker, play_info.target_list, play_info.actions);


    for (auto item : play_info.target_list){
        abstractPower* p = PowerFactory::createPower(powerID::weak, item, effect_w);
        item->add_power(p);
    }

    for (auto item : play_info.target_list){
        abstractPower* p = PowerFactory::createPower(powerID::vulnerable, item, effect_v);
        item->add_power(p);
    }

}

void uppercut::upgrade(){
    effect_v = 2;
    effect_w = 2;
    is_upgraded = true;
    description = generate_description();
}

void uppercut::base_upgrade(){
    base_effect_v = effect_v = 2;
    base_effect_w = effect_w = 2;
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}

void uppercut::combat_reset() {
    abstractAttackCard::combat_reset();
    effect_w = base_effect_w;
    effect_v = base_effect_v;
}




