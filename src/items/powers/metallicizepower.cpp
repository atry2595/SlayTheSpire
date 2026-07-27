#include "metallicizepower.h"

metallicizePower::metallicizePower(abstractEntity* owner_init, int x)
    : abstractPower(tr("Metallicize"), owner_init, x, 999, 0, true, 1)
{
    description = tr("At the end of your/its turn, gain %1 block.").arg(amount);
}


void metallicizePower::at_turn_end(game_action& actions) {
    blockingInfo info;
    info.block = amount * time_affect;
    info.owner = owner;
    info.affected_by_other = false;
    actions.apply_block(info);
}

QString metallicizePower::generate_description(){
    description = tr("At the end of your/its turn, gain %1 block.").arg(amount);
    return description;
}

QString metallicizePower::get_story() {
    return (QObject::tr("Metallicize, a metallic whisper starting deep in the bones, turning skin into living steel.\nThe traveler doesn't need to act—this iron shell grows on its own, as if the body is slowly remembering it was once a mountain."));
}
