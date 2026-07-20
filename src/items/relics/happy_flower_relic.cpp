#include "happy_flower_relic.h"
#include "entity/ironclad.h"

happy_flower_relic::happy_flower_relic(abstractEntity* owner_init)
    :abstractRelic(tr("Happy Flower"), owner_init)
{
    description = tr("Every 3 turns, gain 1 Energy.");
}

QString happy_flower_relic::generate_description(){
    description = tr("Every 3 turns, gain 1 Energy.");
    return description;
}


void happy_flower_relic::at_turn_start(game_action& actions){
    ironclad* player = dynamic_cast<ironclad*>(owner);
    value++;
    if (value >= 3){
        value = 0;
        player->set_energy(player->get_energy() + 1);
    }
}

QString happy_flower_relic::get_story() {
    return (QObject::tr("The Happy Flower, a fixed and innocent smile painted on its petals, sends a healing breeze every few seconds.\nSuch is the merciless irony of the Spire: the happiest thing in the darkest dungeon is a small, plastic flower."));
}
