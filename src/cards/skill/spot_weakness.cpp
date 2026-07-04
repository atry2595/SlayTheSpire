#include "spot_weakness.h"
#include "items/powers/powerfactory.h"
#include "items/powers/abstractpower.h"
#include "entity/abstractenemy.h"

spot_weakness::spot_weakness()
    :abstractSkillCard(tr("Spot Weakness"), "", 1, false, false, false, false)
{
    QString s;
    s += tr("If the enemy intends to attack, gain %1 Strength.").arg(effect);
    base_description = description = s;
}

QString spot_weakness::generate_description(){

    QString s;
    s += tr("If the enemy intends to attack, gain %1 Strength.").arg(effect);
    return s;
}

void spot_weakness::play(playInfo& play_info){
    for (auto item : play_info.target_list){

        abstractEnemy* enemy = dynamic_cast<abstractEnemy*>(item);
        auto mv = enemy->get_intent_list()[enemy->get_current_move()];

        switch (mv.type){
        case (intent_type::attack):
        case (intent_type::attack_block):
        case (intent_type::attack_buff):
        case (intent_type::attack_debuff):{
            abstractPower* power = PowerFactory::createPower(powerID::strength, play_info.attacker, effect);
            if (power) play_info.attacker->add_power(power);
        }
        default:
            return;
        }
    }

}

void spot_weakness::upgrade(){
    effect = 4;
    is_upgraded = true;
    description = generate_description();
}

void spot_weakness::base_upgrade(){
    base_effect = effect = 4;
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}


void spot_weakness::combat_reset() {
    abstractCard::combat_reset();
    effect = base_effect;
}


