#include "ragepower.h"
#include "cards/abstractcard.h"
#include "combat/blocking_info.h"

ragePower::ragePower(abstractEntity* owner_init, int x)
    : abstractPower(tr("Rage"), owner_init, x, 999, 0, true, 1)
{
    description = tr("Whenever you play an Attack this turn, gain %1 Block.").arg(amount);
}


QString ragePower::generate_description(){
    description = tr("Whenever you play an Attack this turn, gain %1 Block.").arg(amount);
    return description;
}

void ragePower::added_time(game_action& actions) {
    play_card_connection = connect(actions.get_event(), &combatEvent::card_played, this,
        [this, &actions](abstractCard* card) {
            if (card->get_card_type() == CardType::attack){
                blockingInfo bl;
                bl.affected_by_other = false;
                bl.block = amount;
                bl.owner = owner;
                actions.apply_block(bl);
            }
        });
}


void ragePower::at_turn_end(game_action&) {
    disconnect(play_card_connection);
    decrease(amount);
}