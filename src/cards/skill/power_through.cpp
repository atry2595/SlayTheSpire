#include "power_through.h"
#include "entity/ironclad.h"
#include "cards/cardfactory.h"

power_through::power_through()
    :abstractSkillCard(tr("Power Through"), "", 1, false, false, false, false)
{
    QString s;
    s += tr("Add 2 Wounds into your hand.");
    s += tr("\nGain %1 block.").arg(block);
    base_description = description = s;
}

QString power_through::generate_description(){

    QString s;
    s += tr("Add 2 Wounds into your hand.");
    s += tr("\nGain %1 block.").arg(block);
    return s;
}

void power_through::play(playInfo& play_info){

    ironclad* player = dynamic_cast<ironclad*>(play_info.attacker);

    for (int i = 0; i < 2 ; i++){
        abstractCard* new_card = CardFactory::createCard(cardID::wound);
        player->hand_pile_add(new_card, true);
    }

    blockingInfo bl;
    bl.block = block;
    bl.owner = play_info.attacker;
    play_info.actions.apply_block(bl);
}

void power_through::upgrade(){
    block = 20;
    is_upgraded = true;
    description = generate_description();
}

void power_through::base_upgrade(){
    base_block = block = 20;
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}

void power_through::combat_reset() {
    abstractCard::combat_reset();
    block = base_block;
}




