#include "ice_cream_relic.h"
#include "entity/ironclad.h"

ice_cream_relic::ice_cream_relic(abstractEntity* owner_init)
    :abstractRelic(tr("Ice Cream"), owner_init)
{
    description = tr("Energy is now conserved between turns.");
}

QString ice_cream_relic::generate_description(){
    description = tr("Energy is now conserved between turns.");
    return description;
}

void ice_cream_relic::added_time(game_action& actions){

    ironclad* player = dynamic_cast<ironclad*>(owner);
    if (!player) return;

    player->set_reset_energy(false);

}

ice_cream_relic::~ice_cream_relic() {
    ironclad* player = dynamic_cast<ironclad*>(owner);
    if (!player) return;

    player->set_reset_energy(true);
}
