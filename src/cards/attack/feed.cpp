#include "feed.h"

feed::feed()
    :abstractAttackCard(tr("Feed"), "", 1, 10, true, false, false, false)
{
    QString s;
    s += tr("Deal %1 damage.").arg(damage);
    s += tr("If Fatal, raise your Max HP by %1. ").arg(effect);
    if (is_exhaust) s += tr("\nExhaust");
    base_description = description = s;
}

QString feed::generate_description(){

    QString s;
    s += tr("Deal %1 damage.").arg(damage);
    s += tr("If Fatal, raise your Max HP by %1. ").arg(effect);
    if (is_exhaust) s += tr("\nExhaust");
    return s;
}

void feed::play(playInfo& play_info){

    attackResult res = perform_attack(play_info.attacker, play_info.target_list, play_info.actions);

    for (auto item : res.results){
        if (item.killed) play_info.attacker->set_max_hp(play_info.attacker->get_max_hp() + effect);
    }

}

void feed::upgrade(){
    damage = 12;
    effect = 4;
    is_upgraded = true;
    description = generate_description();
}

void feed::base_upgrade(){
    base_damage = damage = 12;
    base_effect = effect = 4;
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}

void feed::combat_reset() {
    abstractAttackCard::combat_reset();
    effect = base_effect;
}




