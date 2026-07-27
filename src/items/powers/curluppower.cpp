#include "curluppower.h"
#include "utils/RNG.h"

curlUpPower::curlUpPower(abstractEntity* owner_init, int x)
    : abstractPower(tr("curlup"), owner_init, x, 1, 0, true, 1)
{
    description = tr("Gains (3-7) Block upon first receiving attack damage.");
}


QString curlUpPower::generate_description(){
    description = tr("Gains (3-7) Block upon first receiving attack damage.");
    return description;
}

void curlUpPower::damage_applied(game_action& info){
    blockingInfo bl;
    bl.affected_by_other = false;
    bl.block = RNG::instance().randint(3, 7);
    bl.owner = owner;
    info.apply_block(bl);
    decrease();
}

QString curlUpPower::get_story() {
    return (QObject::tr("Curl Up, an ancient reflex that rounds the body and hides the wounds.\nThe traveler retreats for a moment like a snail into a defensive cocoon, and emerges with a layer of solidity upon their back."));
}
