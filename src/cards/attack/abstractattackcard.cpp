#include "abstractattackcard.h"


abstractAttackCard::abstractAttackCard(QString name_init, QString description_init, int energy_init, int damage_init,
                                       bool upgraded_init, bool exhaust_init, bool retain_init, bool  ethereal_init, bool initial_init)
    :abstractCard(name_init, description_init, energy_init, upgraded_init, exhaust_init, retain_init, ethereal_init, initial_init),
    base_damage(damage_init)
{
    initial_set();
}

void abstractAttackCard::initial_set(){
    damage = base_damage;
}

void abstractAttackCard::reset(){
    abstractCard::reset();
    initial_set();
}

void abstractAttackCard::perform_attack(abstractEntity* attacker, std::vector<abstractEntity*>& target_list, game_action& actions) const {
    attackInfo inf;
    inf.attacker = attacker;
    inf.target_list = target_list;
    inf.damage = damage;

    actions.attack(inf);
}