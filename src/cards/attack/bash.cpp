#include "bash.h"
#include "categories/powers.h"
#include "items/powers/powerfactory.h"

bash::bash()
    :abstractAttackCard(tr("Bash"), "", 2, 8, false, false, false, false)
{
    QString s;
    s += tr("Deal %1 damage.").arg(damage);
    s += tr("\nApply %1 Vulnerable.").arg(effect);
    base_description = description = s;
}

QString bash::generate_description(){

    QString s;
    s += tr("Deal %1 damage.").arg(damage);
    s += tr("\nApply %1 Vulnerable.").arg(effect);
    return s;
}

void bash::play(playInfo& play_info){
    perform_attack(play_info.attacker, play_info.target_list, play_info.actions);

    for (auto item : play_info.target_list){
        abstractPower* p = PowerFactory::createPower(powerID::vulnerable, item, effect);
        item->add_power(p);
    }

}

void bash::upgrade(){
    damage = 10;
    effect = 3;
    is_upgraded = true;
    description = generate_description();
}

void bash::base_upgrade(){
    base_damage = damage = 10;
    base_effect = effect = 3;
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}

void bash::combat_reset() {
    abstractAttackCard::combat_reset();
    effect = base_effect;
}




