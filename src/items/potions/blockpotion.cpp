#include "blockpotion.h"
#include "combat/blocking_info.h"

blockPotion::blockPotion(abstractEntity* owner_init)
    :abstractPotion(tr("Block Potion"), tr("Gain 12 Block."), owner_init)
{}

void blockPotion::play(playInfo& info){
    blockingInfo b;
    b.block = amount;
    b.owner = owner;
    b.affected_by_other = false;

    info.actions.apply_block(b);
}

QString blockPotion::get_story() {
    return (QObject::tr("The Block Potion, a thick cyan liquid sitting motionless in its bottle, as if defending itself from the world.\nThe traveler downs it and for a moment their skin hardens like the Spire's own walls—impenetrable and silent."));
}
