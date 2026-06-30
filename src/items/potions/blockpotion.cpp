#include "blockpotion.h"

blockPotion::blockPotion(abstractEntity* owner_init)
    :abstractPotion(tr("Block Potion"), tr("Gain 12 Block."), owner_init)
{}

void blockPotion::play(playInfo& info){

}