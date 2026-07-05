#include "dexteritypower.h"

dexterityPower::dexterityPower(abstractEntity* owner_init, int x)
    : abstractPower(tr("Dexterity"), owner_init, x, 999, -999, true, 1)
{
    description = tr("Increases block gained by %1").arg(amount);
}

void dexterityPower::modify_blocking(blockingInfo& info) {
    if (info.block > 0) info.block += amount * time_affect;
}

QString dexterityPower::generate_description(){
    description = tr("Increases block gained by %1").arg(amount);
    return description;
}