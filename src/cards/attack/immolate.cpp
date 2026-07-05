#include "immolate.h"
#include "cards/cardfactory.h"
#include "entity/ironclad.h"

immolate::immolate()
    :abstractAttackCard(tr("Immolate"), "", 2, 21, false, false, false, false)
{
    QString s;
    s += tr("Deal %1 damage to ALL enemies.").arg(damage);
    s += tr("\nAdd a Burn into your discard pile.");
    base_description = description = s;
}

QString immolate::generate_description(){

    QString s;
    s += tr("Deal %1 damage to ALL enemies.").arg(damage);
    s += tr("\nAdd a Burn into your discard pile.");
    return s;
}

void immolate::play(playInfo& play_info){

    perform_attack(play_info.attacker, play_info.target_list, play_info.actions);

    abstractCard* nc = CardFactory::createCard(cardID::burn);
    ironclad* player = dynamic_cast<ironclad*>(play_info.attacker);

    if (player)player->discard_pile_add(nc, true);

}

void immolate::upgrade(){
    damage = 28;
    is_upgraded = true;
    description = generate_description();
}

void immolate::base_upgrade(){
    base_damage = damage = 28;
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}

void immolate::combat_reset() {
    abstractAttackCard::combat_reset();
}




