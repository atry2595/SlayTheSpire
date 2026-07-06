#include "preserved_insect_relic.h"
#include "entity/abstractentity.h"
#include "combat/manageCombat/combat_manager.h"

preserved_insect_relic::preserved_insect_relic(abstractEntity* owner_init)
    :abstractRelic(tr("Preserved Insect"), owner_init)
{
    description = tr("Enemies in Elite combats have 25% less HP.");
}

QString preserved_insect_relic::generate_description(){
    description = tr("Enemies in Elite combats have 25% less HP.");
    return description;
}


void preserved_insect_relic::added_time(game_action& actions){
    start_combat_connection = connect(actions.get_event(), &combatEvent::combat_started, this,
        [this, &actions](combat_manager* combat){
        if (combat->get_type() == entityType::elite){

            for (auto item : combat->get_enemies()){
                int newHP = item->get_max_hp() * 0.75;
                item->set_max_hp(newHP);
                item->set_hp(newHP);
            }

        }
    });
}
