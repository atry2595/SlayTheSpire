#include "fairyinabottle.h"
#include "combat/attack_info.h"
#include "entity/abstractentity.h"

fairyInABottle::fairyInABottle(abstractEntity* owner_init)
    :abstractPotion(tr("Fairy in a Bottle"), tr("When you would die, heal to 30%of your Max HP instead and discard this potion."), owner_init)
{}

void fairyInABottle::play(playInfo& info){
    healInfo h;
    h.owner = owner;
    h.value = (int)owner->get_max_hp() * amount;
    info.actions.heal(h);
    disconnect(died_connection);
}

void fairyInABottle::added_time(playInfo& info){
    died_connection = connect(info.actions.get_event(), &combatEvent::entity_killed, this,
        [this, &info](abstractEntity* entity){
        if (entity == owner){
            if (owner->get_hp() == 0){
                play(info);
            }
        }
    });
}