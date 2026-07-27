#include "blood_vial_relic.h"

blood_vial_relic::blood_vial_relic(abstractEntity* owner_init)
    :abstractRelic(tr("Blood Vial"), owner_init)
{
    description = tr("At the start of each combat, heal 2 HP.");
}

QString blood_vial_relic::generate_description(){
    description = tr("At the start of each combat, heal 2 HP.");
    return description;
}


void blood_vial_relic::at_combat_start(game_action& actions){
    healInfo info;
    info.value = 2;
    info.owner = owner;
    actions.heal(info);
}

QString blood_vial_relic::get_story() {
    return (QObject::tr("The Blood Vial's dark liquid dances with every heartbeat of the traveler, as if still alive.\nWhose blood is this? No one knows, but in the heat of battle, it kisses wounds shut, as if an unknown donor still gives from across time."));
}
