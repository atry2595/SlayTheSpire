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