#include "red_mask_relic.h"
#include "items/powers/powerfactory.h"
#include "entity/abstractentity.h"
#include "combat/manageCombat/combat_manager.h"

red_mask_relic::red_mask_relic(abstractEntity* owner_init)
    :abstractRelic(tr("Red Mask"), owner_init)
{
    description = tr("At the start of each combat, apply 1 Weak to ALL enemies.");
}

QString red_mask_relic::generate_description(){
    description = tr("At the start of each combat, apply 1 Weak to ALL enemies.");
    return description;
}


void red_mask_relic::added_time(game_action& actions){
    start_combat_connection = connect(actions.get_event(), &combatEvent::combat_started, this,
        [this, &actions](combat_manager* combat){
            for (auto item : combat->get_enemies()){
                abstractPower* np = PowerFactory::createPower(powerID::weak, item, 1);
                item->add_power(actions, np);
            }
    });
}
