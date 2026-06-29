#include "metallicizepower.h"

metallicizePower::metallicizePower(abstractEntity* owner_init, int x)
    : abstractPower(tr("Metallicize"), owner_init, x, 999, 0, true, 1)
{
    description = tr("At the end of your/its turn, gain %1 block.").arg(amount);
}


void metallicizePower::at_turn_end(game_action& actions) {
    blockingInfo info;
    info.block = amount;
    info.owner = owner;
    info.affected_by_other = false;
    actions.apply_block(info);
}

QString metallicizePower::generate_description(){
    description = tr("At the end of your/its turn, gain %1 block.").arg(amount);
    return description;
}