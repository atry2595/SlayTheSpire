#include "painfulstabpower.h"
#include "entity/ironclad.h"
#include "combat/blocking_info.h"
#include "cards/cardfactory.h"

painfulStabPower::painfulStabPower(abstractEntity* owner_init, int x)
    : abstractPower(tr("Painful Stabs"), owner_init, x, 1, 0, true, 0)
{
    description = tr("Whenever you receive attack damage from this enemy, add 1 Wounds into your discard pile.");
}


QString painfulStabPower::generate_description(){
    description = tr("Whenever you receive attack damage from this enemy, add 1 Wounds into your discard pile.");
    return description;
}

void painfulStabPower::added_time(game_action& actions) {


    add_card_connection = connect(actions.get_event(), &combatEvent::damage_applied, this,
        [this](damageInfo& inf){
        if (inf.attacker == owner && inf.damage >= 0){
            abstractCard* nc = CardFactory::createCard(cardID::wound);
            ironclad* player = dynamic_cast<ironclad*>(inf.target);
            player->discard_pile_add(nc, true);
        }
    });

}

QString painfulStabPower::get_story() {
    return (QObject::tr("Painful Stabs, repeated sharp shadows piling tiny wounds atop each other.\nEach cut is insignificant, but like a bad memory, they accumulate to devour the flesh from within."));
}
