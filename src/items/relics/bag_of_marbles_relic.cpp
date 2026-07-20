#include "bag_of_marbles_relic.h"
#include "items/powers/powerfactory.h"
#include "entity/abstractentity.h"
#include "combat/manageCombat/combat_manager.h"

bag_of_marbles_relic::bag_of_marbles_relic(abstractEntity* owner_init)
    :abstractRelic(tr("Bag Of Marbles"), owner_init)
{
    description = tr("At the start of each combat, apply 1 Vulnerable to ALL enemies.");
}

QString bag_of_marbles_relic::generate_description(){
    description = tr("At the start of each combat, apply 1 Vulnerable to ALL enemies.");
    return description;
}


void bag_of_marbles_relic::added_time(game_action& actions){
    start_combat_connection = connect(actions.get_event(), &combatEvent::combat_started, this,
        [this, &actions](combat_manager* combat){
            for (auto item : combat->get_enemies()){
                abstractPower* np = PowerFactory::createPower(powerID::vulnerable, item, 1);
                item->add_power(actions, np);
            }
    });
}

QString bag_of_marbles_relic::get_story() {
    return (QObject::tr("The Bag of Marbles rattles with a childish, glassy whisper—a relic of games that now end in war.\nThe traveler scatters them across the floor, and the enemy, unsuspecting, slips on the fragile memories of a lost childhood."));
}
