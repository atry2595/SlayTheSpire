#include "the_boot_relic.h"
#include "cards/abstractcard.h"
#include "items/powers/powerfactory.h"

the_boot_relic::the_boot_relic(abstractEntity* owner_init)
    :abstractRelic(tr("The Boot"), owner_init)
{
    description = tr("Whenever you would deal 4 or less unblocked Attack damage, increase it to 5.");
}

QString the_boot_relic::generate_description(){
    description = tr("Whenever you would deal 4 or less unblocked Attack damage, increase it to 5.");
    return description;
}

void the_boot_relic::added_time(game_action& actions){

    before_damage_connection = connect(actions.get_event(), &combatEvent::damage_before_taken, this,
        [this, &actions](damageInfo& info) {
            if (owner == info.attacker && info.damage < 5 && info.damage > 0){
                    info.damage = 5;
                }
        });

}

QString the_boot_relic::get_story() {
    return (QObject::tr("The Boot, worn and mud-caked, reeks of roads traveled and enemies laid flat.\nWhen the foe is down, this boot has the final say: one extra stomp, just to make sure you're staying down."));
}
