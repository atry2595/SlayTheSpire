#include "defend.h"
#include "categories/powers.h"
#include "items/powers/powerfactory.h"

defend::defend()
    :abstractSkillCard(tr("Defend"), "", 1, false, false, false, false)
{
    QString s;
    s += tr("Gain %1 Block.").arg(effect);
    base_description = description = s;
}

QString defend::generate_description(){

    QString s;
    s += tr("Gain %1 Block.").arg(effect);
    return s;
}

void defend::play(playInfo& play_info){
    blockingInfo info;
    info.owner = play_info.attacker;
    info.block = effect;

    play_info.actions.apply_block(info);
}

void defend::upgrade(){
    effect = 8;
    is_upgraded = true;
    description = generate_description();
}

void defend::base_upgrade(){
    base_effect = effect = 8;
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}

void defend::combat_reset() {
    abstractCard::combat_reset();
    effect = base_effect;
}




