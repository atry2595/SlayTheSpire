#include "pommel_strike.h"
#include "entity/ironclad.h"

pommel_strike::pommel_strike()
    :abstractAttackCard(tr("Pommel Strike"), "", 1, 9, false, false, false, false)
{
    QString s;
    s += tr("Deal %1 damage.").arg(damage);
    s += tr("\nDraw %1 card.").arg(count);
    base_description = description = s;
}

QString pommel_strike::generate_description(){

    QString s;
    s += tr("Deal %1 damage.").arg(damage);
    s += tr("\nDraw %1 card.").arg(count);
    return s;
}

void pommel_strike::play(playInfo& play_info){

    perform_attack(play_info.attacker, play_info.target_list, play_info.actions );

    ironclad* player = dynamic_cast<ironclad*>(play_info.attacker);
    for (int i = 0; i<count; i++){
        player->draw_card();
    }
}

void pommel_strike::upgrade(){
    damage = 10;
    count = 2;
    is_upgraded = true;
    description = generate_description();
}

void pommel_strike::base_upgrade(){
    base_damage = damage = 10;
    base_count = count = 2;
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}

void pommel_strike::combat_reset() {
    abstractAttackCard::combat_reset();
    count = base_count;
}

