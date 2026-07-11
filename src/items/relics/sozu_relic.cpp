#include "sozu_relic.h"
#include "entity/abstractentity.h"
#include "entity/ironclad.h"
#include "items/potions/abstractpotion.h"

sozu_relic::sozu_relic(abstractEntity* owner_init)
    :abstractRelic(tr("Sozu"), owner_init)
{
    description = tr("Gain 1 Energy at the start of your turn. You can no longer obtain potions.");
}

QString sozu_relic::generate_description(){
    description = tr("Gain 1 Energy at the start of your turn. You can no longer obtain potions.");
    return description;
}


void sozu_relic::added_time(game_action& actions){
    ironclad* player = dynamic_cast<ironclad*>(owner);
    if (!player) return;
    player->set_base_energy(player->get_base_energy() + 1);

    abstractPotion::lock = true;
}
