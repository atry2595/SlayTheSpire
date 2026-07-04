#include "bloodletting.h"
#include "entity/ironclad.h"

bloodletting::bloodletting()
    :abstractSkillCard(tr("Bloodletting"), "", 0, false, false, false, false)
{
    QString s;
    s += tr("Lose 3 HP.");
    s += tr("\nGain %1 Energy.").arg(count);
    base_description = description = s;
}

QString bloodletting::generate_description(){

    QString s;
    s += tr("Lose 3 HP.");
    s += tr("\nGain %1 Energy.").arg(count);
    return s;
}

void bloodletting::play(playInfo& play_info){

    ironclad* player = dynamic_cast<ironclad*>(play_info.attacker);

    damageInfo info;
    info.damage = 3;
    info.attacker = nullptr;
    info.target = play_info.attacker;
    info.block_active = false;

    play_info.actions.apply_damage(info);
    player->set_energy(player->get_energy() + count);

}

void bloodletting::upgrade(){
    count = 3;
    is_upgraded = true;
    description = generate_description();
}

void bloodletting::base_upgrade(){
    base_count = count = 3;
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}

void bloodletting::combat_reset() {
    abstractCard::combat_reset();
    count = base_count;
}




