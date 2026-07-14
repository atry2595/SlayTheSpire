#include "golden_idol_relic.h"
#include "entity/abstractentity.h"
#include "combat/manageCombat/combat_manager.h"

golden_idol_relic::golden_idol_relic(abstractEntity* owner_init)
    :abstractRelic(tr("Golden Idol"), owner_init)
{
    description = tr("Enemies drop 20 more Gold.");
}

QString golden_idol_relic::generate_description(){
    description = tr("Enemies drop 20 more Gold.");
    return description;
}


void golden_idol_relic::added_time(game_action& actions){
    end_combat_connection = connect(actions.get_event(), &combatEvent::combat_ended, this,
        [this](combat_manager* comb, bool vic){
        if (vic && this->owner->get_hp()) {
            comb->add_coin_to_reward(owner, 20);
        }
    });
}
