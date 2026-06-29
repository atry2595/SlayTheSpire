#include "strengthpower.h"

strengthPower::strengthPower(abstractEntity* owner_init, int x)
    : abstractPower(tr("Strength"), owner_init, x, 999, -999, true)
{
    description = tr("Increases attack damage by %1").arg(amount);
}


void strengthPower::modify_attack(attackInfo& info) {
    info.damage += amount;
}

QString strengthPower::generate_description(){
    description = tr("Increases attack damage by %1").arg(amount);
    return description;
}