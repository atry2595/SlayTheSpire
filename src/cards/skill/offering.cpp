#include "offering.h"
#include "entity/ironclad.h"

offering::offering()
    :abstractSkillCard(tr("Offering"), "", 0, true, false, false, false)
{
    QString s;
    s += tr("Lose 6 HP.");
    s += tr("\nGain 2 Energy.");
    s += tr("\nDraw %1 cards.").arg(count);
    if (is_exhaust) s += tr("\nExhaust.");
    base_description = description = s;
}

QString offering::generate_description(){

    QString s;
    s += tr("Lose 6 HP.");
    s += tr("\nGain 2 Energy.");
    s += tr("\nDraw %1 cards.").arg(count);
    if (is_exhaust) s += tr("\nExhaust.");
    return s;
}

void offering::play(playInfo& play_info){

    ironclad* player = dynamic_cast<ironclad*>(play_info.attacker);

    damageInfo info;
    info.damage = 6;
    info.attacker = nullptr;
    info.target = play_info.attacker;

    play_info.actions.apply_damage(info);
    player->set_energy(player->get_energy() + 2);
    for (int i = 0; i < count; i++) player->draw_card();

}

void offering::upgrade(){
    count = 5;
    is_upgraded = true;
    description = generate_description();
}

void offering::base_upgrade(){
    base_count = count = 5;
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}

void offering::combat_reset() {
    abstractCard::combat_reset();
    count = base_count;
}




