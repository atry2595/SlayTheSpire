#include "clash.h"
#include "entity/ironclad.h"

clash::clash()
    :abstractAttackCard(tr("Clash"), "", 0, 14, false, false, false, false)
{
    QString s;
    s += tr("Can only be played if every card in your hand is an Attack.");
    s += tr("\nDeal %1 damage.").arg(damage);
    base_description = description = s;
}

QString clash::generate_description(){

    QString s;
    s += tr("Can only be played if every card in your hand is an Attack.");
    s += tr("\nDeal %1 damage.").arg(damage);
    return s;
}

void clash::play(playInfo& play_info){

    if (available)
        perform_attack(play_info.attacker, play_info.target_list, play_info.actions );

}

void clash::upgrade(){
    damage = 18;
    is_upgraded = true;
    description = generate_description();
}

void clash::base_upgrade(){
    base_damage = damage = 18;
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}

void clash::combat_reset() {
    abstractAttackCard::combat_reset();
}


void clash::update(playInfo& info){
    abstractCard::update(info);
    ironclad* player = dynamic_cast<ironclad*>(info.attacker);
    for (auto item : player->get_hand_pile()) {
        if (item->get_card_type() != CardType::attack){
            available = false;
            return;
        }
    }
    available = true;
}