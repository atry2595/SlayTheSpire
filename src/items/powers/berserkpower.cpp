#include "berserkpower.h"
#include "entity/ironclad.h"
#include "combat/blocking_info.h"


berserkPower::berserkPower(abstractEntity* owner_init, int x)
    : abstractPower(tr("Berserk"), owner_init, x, 999, 0, true, 1)
{
    description = tr("At the start of your turn, gain %1 Energy.").arg(amount);
}


QString berserkPower::generate_description(){
    description = tr("At the start of your turn, gain %1 Energy.").arg(amount);
    return description;
}


void berserkPower::at_turn_start(game_action& actions) {

    ironclad* player = dynamic_cast<ironclad*>(owner);
    player->set_energy(player->get_energy() + amount);
}

QString berserkPower::get_story() {
    return (QObject::tr("Berserk, a mad thirst holding the traveler on the edge between power and vulnerability.\nGrowing energy in exchange for a crack in the armor—as if every true power must exact a steep toll from the body."));
}
