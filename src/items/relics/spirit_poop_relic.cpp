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
