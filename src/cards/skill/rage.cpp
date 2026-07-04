#include "rage.h"
#include "items/powers/powerfactory.h"

rage::rage()
    :abstractSkillCard(tr("Rage"), "", 0, false, false, false, false)
{
    QString s;
    s += tr("Whenever you play an Attack this turn, gain %1 Block.").arg(block);
    base_description = description = s;
}

QString rage::generate_description(){

    QString s;
    s += tr("Whenever you play an Attack this turn, gain %1 Block.").arg(block);
    return s;
}

void rage::play(playInfo& play_info){

    abstractPower* np = PowerFactory::createPower(powerID::rage, play_info.attacker, block);
    play_info.attacker->add_power(np);

}

void rage::upgrade(){
    block = 5;
    is_upgraded = true;
    description = generate_description();
}

void rage::base_upgrade(){
    base_block = block = 5;
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}

void rage::combat_reset() {
    abstractCard::combat_reset();
    block = base_block;
}




