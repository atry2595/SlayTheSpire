#include "abstractattackcard.h"

abstractAttackCard::abstractAttackCard(QString name_init, QString description_init, int energy_init, int damage_init,
                                       bool upgraded_init, bool exhaust_init, bool retain_init, bool  ethereal_init, bool initial_init)
    :abstractCard(name_init, description_init, CardType::attack, energy_init, upgraded_init, exhaust_init, retain_init, ethereal_init, initial_init),
    base_damage(damage_init)
{
    init();
}

void abstractAttackCard::init(){
    damage = base_damage;
}

void abstractAttackCard::reset(){
    abstractCard::reset();
    init();
}

void abstractAttackCard::play(){
    //play sound
}