#include "spirit_poop_relic.h"

spirit_poop_relic::spirit_poop_relic(abstractEntity* owner_init)
    :abstractRelic(tr("Spirit Poop"), owner_init)
{
    description = tr("It's unpleasant.");
}

QString spirit_poop_relic::generate_description(){
    description = tr("It's unpleasant.");
    return description;
}

QString spirit_poop_relic::get_story() {
    return (QObject::tr("Spirit Poop, a gift the Spire's spirits bestowed upon the traveler with biting sarcasm.\nWorthless, odorless, and utterly useless, yet within this absolute nothingness lies a bitter smile: a souvenir that the Spire, even in its generosity, is still mocking you."));
}
