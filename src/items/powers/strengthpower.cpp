#include "strengthpower.h"

strengthPower::strengthPower(abstractEntity* owner_init, int x)
    : abstractPower(tr("Strength"), owner_init, x, 999, -999, true, 0)
{
    description = tr("Increases attack damage by %1").arg(amount);
}


void strengthPower::modify_attack(attackInfo& info) {
    info.damage += amount * time_affect;
}

QString strengthPower::generate_description(){
    description = tr("Increases attack damage by %1").arg(amount);
    return description;
}

QString strengthPower::get_story() {
    return (QObject::tr("Strength, a red phantom nesting in the traveler's fists, making each strike heavier than the last.\nIt's not just muscle that grows—it's concentrated fury driving the blade deeper into the enemy's flesh."));
}
