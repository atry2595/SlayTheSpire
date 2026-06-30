#include "entrench.h"

entrench::entrench()
    :abstractSkillCard(tr("Entrench"), "", 2, false, false, false, false)
{
    QString s;
    s += tr("Double your Block.");
    if (is_exhaust) s+= tr("\nExhaust.");
    base_description = description = s;
}

QString entrench::generate_description(){

    QString s;
    s += tr("Double your Block.");
    if (is_exhaust) s+= tr("\nExhaust.");
    return s;
}

void entrench::play(playInfo& play_info){
    int new_block = play_info.attacker->get_block() * 2;
    play_info.attacker->set_block(new_block);
}

void entrench::upgrade(){
    energy = 1;
    is_upgraded = true;
    description = generate_description();
}

void entrench::base_upgrade(){
    base_energy = energy = 1;
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}





