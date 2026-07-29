#include "heavy_blade.h"
#include "entity/ironclad.h"
#include "items/powers/abstractpower.h"

heavy_blade::heavy_blade()
    :abstractAttackCard(tr("Heavy Blade"), "", 2, 14, false, false, false, false)
{
    QString s;
    s += tr("Deal %1 damage. Strength affects this card %2 times.").arg(damage).arg(effect);
    base_description = description = s;
}

QString heavy_blade::generate_description(){

    QString s;
    s += tr("Deal %1 damage. Strength affects this card %2 times.").arg(damage).arg(effect);
    return s;
}

void heavy_blade::play(playInfo& play_info){

    auto pwr = play_info.attacker->get_spec_power(powerID::strength);
    if (pwr){
        int old_time = pwr->get_time_affect();
        pwr->set_time_affect(old_time * effect);
    }

    perform_attack(play_info.attacker, play_info.target_list, play_info.actions );

    if (pwr){
        int new_time = pwr->get_time_affect();
        pwr->set_time_affect(new_time / effect);
    }

}

void heavy_blade::upgrade(){
    effect = 5;
    is_upgraded = true;
    description = generate_description();
}

void heavy_blade::base_upgrade(){
    base_effect = effect = 5;
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}

void heavy_blade::combat_reset() {
    abstractAttackCard::combat_reset();
    effect = base_effect;
}
