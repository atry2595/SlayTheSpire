#include "philosophers_stone_relic.h"
#include "entity/abstractentity.h"
#include "entity/ironclad.h"
#include "combat/manageCombat/combat_manager.h"
#include "items/powers/powerfactory.h"

philosophers_stone_relic::philosophers_stone_relic(abstractEntity* owner_init)
    :abstractRelic(tr("Philosopher's Stone"), owner_init)
{
    description = tr("Gain 1 Energy at the start of your turn. ALL enemies start combat with 1 Strength.");
}

QString philosophers_stone_relic::generate_description(){
    description = tr("Gain 1 Energy at the start of your turn. ALL enemies start combat with 1 Strength.");
    return description;
}


void philosophers_stone_relic::added_time(game_action& actions){
    ironclad* player = dynamic_cast<ironclad*>(owner);
    if (!player) return;
    player->set_base_energy(player->get_base_energy() + 1);

    game_start_connection = connect(actions.get_event(), &combatEvent::combat_started, this,
        [this, &actions](combat_manager* info){
            for (auto item : info->get_enemies()){
                abstractPower* np = PowerFactory::createPower(powerID::strength, item, 1);
                item->add_power(actions, np);
            }
    });
}
