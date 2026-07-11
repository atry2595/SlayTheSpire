#include "red_skull_relic.h"
#include "items/powers/powerfactory.h"
#include "entity/abstractentity.h"
#include "combat/manageCombat/combat_manager.h"

red_skull_relic::red_skull_relic(abstractEntity* owner_init)
    :abstractRelic(tr("Red Skull"), owner_init)
{
    description = tr("While your HP is at or below 50%, you have 3 additional Strength.");
}

QString red_skull_relic::generate_description(){
    description = tr("While your HP is at or below 50%, you have 3 additional Strength.");
    return description;
}


void red_skull_relic::added_time(game_action& actions){
    half_hp_connection = connect(actions.get_event(), &combatEvent::hp_changed, this,
        [this, &actions](abstractEntity* entity, int oldHP, int newHP){
        if (entity == owner){
            if (newHP <= owner->get_max_hp() / 2 && is_active == false){
                abstractPower* np = PowerFactory::createPower(powerID::strength, owner, 3);
                owner->add_power(actions, np);
                is_active = true;
            }
            else if(newHP > owner->get_max_hp() / 2 && is_active == true){
                abstractPower* np = PowerFactory::createPower(powerID::strength, owner, -3);
                owner->add_power(actions, np);
                is_active = false;
            }
        }
    });
}
