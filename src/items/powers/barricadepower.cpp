#include "barricadepower.h"

barricadePower::barricadePower(abstractEntity* owner_init, int x)
    : abstractPower(tr("Barricade"), owner_init, x, 1, 0, true, 1)
{
    description = tr("Block is not removed at the start of your/its turn.");
}


QString barricadePower::generate_description(){
    description = tr("Block is not removed at the start of your/its turn.");
    return description;
}

void barricadePower::added_time(game_action&) {
    owner->set_reset_block(false);
}

QString barricadePower::get_story() {
    return (QObject::tr("Barricade, an invisible wall the traveler draws around themselves, and their armor never crumbles again.\nThe block they build today remains until tomorrow, as if time no longer has the right to take their defense back."));
}
