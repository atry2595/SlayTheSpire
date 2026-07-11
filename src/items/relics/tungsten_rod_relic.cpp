#include "tungsten_rod_relic.h"
#include "entity/abstractentity.h"

tungsten_rod_relic::tungsten_rod_relic(abstractEntity* owner_init)
    :abstractRelic(tr("Tungsten Rod"), owner_init)
{
    description = tr("Whenever you would lose HP, lose 1 less.");
}

QString tungsten_rod_relic::generate_description(){
    description = tr("Whenever you would lose HP, lose 1 less.");
    return description;
}

void tungsten_rod_relic::added_time(game_action& actions){
    before_damage_connection = connect(actions.get_event(), &combatEvent::damage_before_taken, this,
        [this, &actions](damageInfo& info) {
            if (owner == info.target && info.damage > 0){
                info.damage--;
            }
        });
}
