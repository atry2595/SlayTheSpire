#include "blood_for_blood.h"
#include "entity/ironclad.h"

blood_for_blood::blood_for_blood()
    :abstractAttackCard(tr("Blodd For Blood"), "", 4, 18, false, false, false, false)
{
    QString s;
    s += tr("Costs 1 less Energy for each time you lose HP this combat.");
    s += tr("\nDeal %1 damage.").arg(damage);
    base_description = description = s;
}

QString blood_for_blood::generate_description(){

    QString s;
    s += tr("Costs 1 less Energy for each time you lose HP this combat.");
    s += tr("\nDeal %1 damage.").arg(damage);
    return s;
}

void blood_for_blood::play(playInfo& play_info){

    perform_attack(play_info.attacker, play_info.target_list, play_info.actions );
}

void blood_for_blood::upgrade(){
    damage = 22;
    energy = std::min(3, energy);
    is_upgraded = true;
    description = generate_description();
}

void blood_for_blood::base_upgrade(){
    base_damage = damage = 22;
    base_energy = 3;
    energy = std::min(base_energy, energy);
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}

void blood_for_blood::combat_reset() {
    abstractAttackCard::combat_reset();
}

void blood_for_blood::damage_applied() {
    energy = std::max(0, energy - 1);
}


