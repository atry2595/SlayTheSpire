#include "enragepower.h"
#include "powerfactory.h"
#include "combat/blocking_info.h"
#include "cards/abstractcard.h"

enragePower::enragePower(abstractEntity* owner_init, int x)
    : abstractPower(tr("Enrage"), owner_init, x, 999, 0, true, 1)
{
    description = tr("Whenever a Skill card is played, gain %1 Strength.").arg(amount);
}


QString enragePower::generate_description(){
    description = tr("Whenever a Skill card is played, gain %1 Strength.").arg(amount);
    return description;
}

void enragePower::added_time(game_action& actions) {
    play_card_connection = connect(actions.get_event(), &combatEvent::card_played, this,
        [this, &actions](playCardInfo& card) {
            if (card.card->get_card_type() == CardType::skill){
                abstractPower* np = PowerFactory::createPower(powerID::strength, owner, amount);
                owner->add_power(actions, np);
            }
        });
}

QString enragePower::get_story() {
    return (QObject::tr("Enrage, a flame that grows from wounds, turning pain into power.\nEvery blow the traveler takes is not an injury but an invitation to a louder roar, as if spilled blood becomes the fuel of an inner fire."));
}
