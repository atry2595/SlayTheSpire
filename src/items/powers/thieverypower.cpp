#include "thieverypower.h"
#include "entity/ironclad.h"
#include "combat/blocking_info.h"
#include "cards/cardfactory.h"

thieveryPower::thieveryPower(abstractEntity* owner_init, int x)
    : abstractPower(tr("Thievery"), owner_init, x, 999, 0, true, 1)
{
    description = tr("Steals %1 Gold whenever it attacks.").arg(amount);
}


QString thieveryPower::generate_description(){
    description = tr("Steals %1 Gold whenever it attacks.").arg(amount);
    return description;
}

void thieveryPower::added_time(game_action& actions) {

    attack_connection = connect(actions.get_event(), &combatEvent::attack_started, this,
        [this](attackInfo& inf){
        if (inf.attacker == owner && inf.attack_type == attackType::intent){
            for (auto item : inf.target_list){
                owner->earn_coin(item->lose_gold(amount));
            }
        }
    });

}
