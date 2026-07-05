#include "shrug_it_off.h"
#include "entity/ironclad.h"

shrug_it_off::shrug_it_off()
    :abstractSkillCard(tr("Shrug It Off"), "", 1, false, false, false, false)
{
    QString s;
    s += tr("Gain %1 block.").arg(block);
    s += tr("\nDraw 1 card.");
    base_description = description = s;
}

QString shrug_it_off::generate_description(){

    QString s;
    s += tr("Gain %1 block.").arg(block);
    s += tr("\nDraw 1 card.");
    return s;
}

void shrug_it_off::play(playInfo& play_info){

    ironclad* player = dynamic_cast<ironclad*>(play_info.attacker);

    blockingInfo bl;
    bl.block = block;
    bl.owner = play_info.attacker;
    play_info.actions.apply_block(bl);

    player->draw_card();
}

void shrug_it_off::upgrade(){
    block = 11;
    is_upgraded = true;
    description = generate_description();
}

void shrug_it_off::base_upgrade(){
    base_block = block = 11;
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}

void shrug_it_off::combat_reset() {
    abstractCard::combat_reset();
    block = base_block;
}




