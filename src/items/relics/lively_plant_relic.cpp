#include "lively_plant_relic.h"
#include "entity/abstractentity.h"
#include "ui/restpage/restpage.h"

lively_plant_relic::lively_plant_relic(abstractEntity* owner_init)
    :abstractRelic(tr("Lively Plant"), owner_init)
{
    description = tr("Gain 1 Energy at the start of your turn. You can no longer Rest at Rest Sites.");
}

QString lively_plant_relic::generate_description(){
    description = tr("Gain 1 Energy at the start of your turn. You can no longer Rest at Rest Sites.");
    return description;
}


void lively_plant_relic::added_time(game_action& actions){
    RestPage::can_rest = false;
}

QString lively_plant_relic::get_story() {
    return (QObject::tr("The Lively Plant, a tiny vine in a cracked pot, turns its leaves toward violence with strange eagerness.\nWith every strike the traveler lands, this plant drinks and grows, as if violence is its sunlight and it grows livelier just watching the fight."));
}
