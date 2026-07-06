#include "burning_blood_relic.h"

burning_blood_relic::burning_blood_relic(abstractEntity* owner_init)
    :abstractRelic(tr("Burning Blood"), owner_init)
{
    description = tr("At the end of combat, heal %1 HP.").arg(value);
}

QString burning_blood_relic::generate_description(){
    description = tr("At the end of combat, heal %1 HP.").arg(value);
    return description;
}

void burning_blood_relic::at_combat_end(game_action& actions){
    healInfo h_info;
    h_info.owner = owner;
    h_info.value = value;

    actions.heal(h_info);
}
