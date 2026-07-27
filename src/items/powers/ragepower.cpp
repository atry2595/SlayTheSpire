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
        [this, &actions](playCardInfo& card) {
            if (card.card->get_card_type() == CardType::attack && card.owner == owner){
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

QString ragePower::get_story() {
    return (QObject::tr("Rage, a brief but ferocious storm that turns fists to iron for a few heartbeats.\nThe traveler feeds on this short-lived flame and spins a block of pure instinct around themselves, as if the purest power is the kind that doesn't linger but shatters."));
}
