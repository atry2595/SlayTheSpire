#include "helmet_of_the_cleric_relic.h"
#include "entity/abstractentity.h"

helmet_of_cleric_relic::helmet_of_cleric_relic(abstractEntity* owner_init)
    :abstractRelic(tr("Helmet Of Cleric"), owner_init)
{
    description = tr("At the end of combat, raise your Max HP by 1.");
}

QString helmet_of_cleric_relic::generate_description(){
    description = tr("At the end of combat, raise your Max HP by 1.");
    return description;
}
void helmet_of_cleric_relic::at_combat_end(game_action&){
    owner->set_max_hp(owner->get_max_hp() + 1);
}

QString helmet_of_cleric_relic::get_story() {
    return (QObject::tr("The Helmet of the Cleric, its metal still vibrating with old prayers its owner never finished.\nThe traveler wears it and a halo of devotional calm wraps around them, as if this metal turns faith into a physical shield."));
}
