#include "kunai_relic.h"
#include "cards/abstractcard.h"
#include "items/powers/powerfactory.h"

kunai_relic::kunai_relic(abstractEntity* owner_init)
    :abstractRelic(tr("Kunai"), owner_init)
{
    description = tr("Every time you play 3 Attacks in a single turn, gain 1 Dexterity");
}

QString kunai_relic::generate_description(){
    description = tr("Every time you play 3 Attacks in a single turn, gain 1 Dexterity");
    return description;
}

void kunai_relic::added_time(game_action& actions){

    play_card_connection = connect(actions.get_event(), &combatEvent::card_played, this,
        [this, &actions](playCardInfo& card_info) {
            if (card_info.card->get_card_type() == CardType::attack && owner == card_info.owner){
                value++;
                if (value == 3){
                value = 0;
                abstractPower* np = PowerFactory::createPower(powerID::dexterity, owner, 1);
                owner->add_power(actions, np);
                }
            }

    });

}

void kunai_relic::at_turn_start(game_action& actions){
    value = 0;
}

QString kunai_relic::get_story() {
    return (QObject::tr("The Kunai, the Shuriken's heavier sister, demands more power with every strike and spins a deeper cut.\nIn the darkness of battle, it whirls and lands like a one-winged bird, a reminder that elegance can be ruthless too."));
}
