#include "gremlin_horn_relic.h"
#include "entity/abstractentity.h"
#include "entity/ironclad.h"

gremlin_horn_relic::gremlin_horn_relic(abstractEntity* owner_init)
    :abstractRelic(tr("Gremlin Horn"), owner_init)
{
    description = tr("Whenever an enemy dies, gain 1 Energy and draw 1 card.");
}

QString gremlin_horn_relic::generate_description(){
    description = tr("Whenever an enemy dies, gain 1 Energy and draw 1 card.");
    return description;
}


void gremlin_horn_relic::added_time(game_action& actions){
    enemy_killed_connection = connect(actions.get_event(), &combatEvent::entity_killed, this,
        [this](abstractEntity* entity){
        if (entity->get_type() == entityType::monster ||
            entity->get_type() == entityType::elite ||
            entity->get_type() == entityType::boss) {
            ironclad* player = dynamic_cast<ironclad*>(owner);
            if (!player) return;
            player->set_energy(player->get_energy() + 1);
            player->draw_card();
        }
    });
}
