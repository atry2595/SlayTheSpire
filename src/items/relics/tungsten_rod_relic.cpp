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

QString tungsten_rod_relic::get_story() {
    return (QObject::tr("The Tungsten Rod, heavy and cold, holds a dull and unyielding glimmer.\nIt promises the traveler: whatever you lose, some of it stays right here, as if this stubborn cosmic metal has simply never learned how to forget a loss."));
}
