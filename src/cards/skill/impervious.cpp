#include "impervious.h"

impervious::impervious()
    :abstractSkillCard(tr("Impervious"), "", 2, true, false, false, false)
{
    QString s;
    s += tr("Gain %1 Block.").arg(effect);
    if (is_exhaust) s+= tr("\nExhaust.");
    base_description = description = s;
}

QString impervious::generate_description(){

    QString s;
    s += tr("Gain %1 Block.").arg(effect);
    if (is_exhaust) s+= tr("\nExhaust.");
    return s;
}

void impervious::play(playInfo& play_info){
    blockingInfo info;
    info.owner = play_info.attacker;
    info.block = effect;

    play_info.actions.apply_block(info);
}

void impervious::upgrade(){
    effect = 40;
    is_upgraded = true;
    description = generate_description();
}

void impervious::base_upgrade(){
    base_effect = effect = 40;
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}

void impervious::combat_reset() {
    abstractCard::combat_reset();
    effect = base_effect;
}




