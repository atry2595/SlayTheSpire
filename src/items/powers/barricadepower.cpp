#include "barricadepower.h"

barricadePower::barricadePower(abstractEntity* owner_init, int x)
    : abstractPower(tr("Barricade"), owner_init, x, 1, 0, true, 1)
{
    description = tr("Block is not removed at the start of your/its turn.");
    owner->set_reset_block(false);
}


QString barricadePower::generate_description(){
    description = tr("Block is not removed at the start of your/its turn.");
    return description;
}