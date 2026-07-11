#include "black_star_relic.h"
#include "entity/abstractentity.h"
#include "combat/manageCombat/combat_manager.h"
#include "relicfactory.h"

black_star_relic::black_star_relic(abstractEntity* owner_init)
    :abstractRelic(tr("Black Star"), owner_init)
{
    description = tr("Elites now drop an additional relic when defeated.");
}

QString black_star_relic::generate_description(){
    description = tr("Elites now drop an additional relic when defeated.");
    return description;
}


void black_star_relic::added_time(game_action& actions){
    start_combat_connection = connect(actions.get_event(), &combatEvent::combat_started, this,
        [this, &actions](combat_manager* combat){
        if (combat->get_type() == entityType::elite){

            RNG& rng = RNG::instance();
            std::vector<relicID> commons = common_relic;
            rng.shuffle(commons);

            relicID selected = commons[0];

            for (auto item : commons) {

                if (owner->get_spec_relic(item) != nullptr)
                    continue;

                selected = item;
                break;
            }

            combat->add_relic_to_reward(owner, RelicFactory::createRelic(selected, owner));

        }
    });
}
