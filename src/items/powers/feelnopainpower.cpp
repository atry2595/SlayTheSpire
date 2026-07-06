#include "feelNoPainpower.h"
#include "cards/abstractcard.h"
#include "combat/blocking_info.h"

feelNoPainPower::feelNoPainPower(abstractEntity* owner_init, int x)
    : abstractPower(tr("Feel No Pain"), owner_init, x, 999, 0, true, 1)
{
    description = tr("Whenever you Exhaust a card, gain %1 Block.").arg(amount);
}


QString feelNoPainPower::generate_description(){
    description = tr("Whenever you Exhaust a card, gain %1 Block.").arg(amount);
    return description;
}

void feelNoPainPower::added_time(game_action& actions) {
    exhaust_card_connection = connect(actions.get_event(), &combatEvent::card_moved, this,
        [this, &actions](playCardInfo& card, PileType from, PileType to) {
            if (to == PileType::exhaust && card.owner == owner){
                blockingInfo bl;
                bl.affected_by_other = false;
                bl.block = amount;
                bl.owner = owner;
                actions.apply_block(bl);
            }
        });
}