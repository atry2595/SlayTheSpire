#include "jax.h"
#include "items/powers/powerfactory.h"

JAX::JAX()
    :abstractSkillCard(tr("J.A.X."), "", 0, false, false, false, false)
{
    QString s;
    s += tr("Lose %1 HP.").arg(dmg);
    s += tr("\nGain %1 Strength.").arg(effect);
    base_description = description = s;
}

QString JAX::generate_description(){

    QString s;
    s += tr("Lose %1 HP.").arg(dmg);
    s += tr("\nGain %1 Strength.").arg(effect);
    return s;
}

void JAX::play(playInfo& play_info){
    damageInfo dmg_info;
    dmg_info.damage = dmg;
    dmg_info.attacker = nullptr;
    dmg_info.target = play_info.attacker;

    play_info.actions.apply_damage(dmg_info);

    abstractPower* p = PowerFactory::createPower(powerID::strength, play_info.attacker, effect);

    play_info.attacker->add_power(p);
}

void JAX::upgrade(){
    effect = 3;
    is_upgraded = true;
    description = generate_description();
}

void JAX::base_upgrade(){
    base_effect = effect = 3;
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}

void JAX::combat_reset() {
    abstractCard::combat_reset();
    effect = base_effect;
}




