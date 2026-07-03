#include "perfected_strike.h"
#include "entity/ironclad.h"

perfected_strike::perfected_strike()
    :abstractAttackCard(tr("Perfected Strike"), "", 2, 6, false, false, false, false)
{
    QString s;
    s += tr("Deal %1 damage.").arg(damage);
    s += tr("\nDeals %1 additional damage for ALL your cards containing \"Strike\".").arg(addit_dmg);
    base_description = description = s;
}

QString perfected_strike::generate_description(){

    QString s;
    s += tr("Deal %1 damage.").arg(damage);
    s += tr("\nDeals %1 additional damage for ALL your cards containing \"Strike\".").arg(addit_dmg);
    return s;
}

void perfected_strike::play(playInfo& play_info){

    int additional = 0;
    ironclad* player = dynamic_cast<ironclad*>(play_info.attacker);
    for (auto item : player->get_combat_deck()){
        additional += addit_dmg * item->is_strike();
    }
    damage += additional;
    perform_attack(play_info.attacker, play_info.target_list, play_info.actions );
    damage -= additional;
}

void perfected_strike::upgrade(){
    addit_dmg = 3;
    is_upgraded = true;
    description = generate_description();
}

void perfected_strike::base_upgrade(){
    base_addit_dmg = addit_dmg = 3;
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}

void perfected_strike::combat_reset() {
    abstractAttackCard::combat_reset();
    addit_dmg = base_addit_dmg;
}

