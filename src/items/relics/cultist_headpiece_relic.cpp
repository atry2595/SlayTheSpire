#include "cultist_headpiece_relic.h"
#include "entity/abstractentity.h"
#include "assetsManager/soundmanager.h"

cultist_headpiece_relic::cultist_headpiece_relic(abstractEntity* owner_init)
    :abstractRelic(tr("Cutist Headpiece"), owner_init)
{
    description = tr("You feel more talkative.");
}

QString cultist_headpiece_relic::generate_description(){
    description = tr("You feel more talkative.");
    return description;
}


void cultist_headpiece_relic::at_combat_start(game_action& actions){
    soundManager::instance().playSoundEffect(SoundEffect::cawCaw);
}

QString cultist_headpiece_relic::get_story() {
    return (QObject::tr("The Cultist Headpiece, its bony beak still imprisoning the whisper of \"Caw! Caw!\"\nDonning it, the traveler hears the duck-like voice of power inside their own skull and understands that ascension always begins with the sacrifice of silence."));
}
