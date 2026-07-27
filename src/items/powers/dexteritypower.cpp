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

QString dexterityPower::get_story() {
    return (QObject::tr("Dexterity, the blue essence of evasion running through veins, making skin slipperier than ice.\nThe traveler sees the blow, but the blow doesn't fully see them back—as if a layer of \"almost\" now separates their flesh from the enemy's blade."));
}
