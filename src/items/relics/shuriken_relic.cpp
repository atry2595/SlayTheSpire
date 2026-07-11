#include "shuriken_relic.h"
#include "cards/abstractcard.h"
#include "items/powers/powerfactory.h"

shuriken_relic::shuriken_relic(abstractEntity* owner_init)
    :abstractRelic(tr("Shuriken"), owner_init)
{
    description = tr("Every time you play 3 Attacks in a single turn, gain 1 Strength.");
}

QString shuriken_relic::generate_description(){
    description = tr("Every time you play 3 Attacks in a single turn, gain 1 Strength.");
    return description;
}

void shuriken_relic::added_time(game_action& actions){

    play_card_connection = connect(actions.get_event(), &combatEvent::card_played, this,
        [this, &actions](playCardInfo& card_info) {
            if (card_info.card->get_card_type() == CardType::attack && owner == card_info.owner){
                value++;
                if (value == 3){
                value = 0;
                abstractPower* np = PowerFactory::createPower(powerID::strength, owner, 1);
                owner->add_power(actions, np);
                }
            }

    });

}

void shuriken_relic::at_turn_start(game_action& actions){
    value = 0;
}