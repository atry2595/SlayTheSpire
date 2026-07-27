#include "vulnerablePower.h"

vulnerablePower::vulnerablePower(abstractEntity* owner_init, int x)
    : abstractPower(tr("Vulnerable"), owner_init, x, 999, 0, false, 2)
{
    description = tr("Receive 50% more damage from Attacks for %1 turns.").arg(amount);
}


void vulnerablePower::modify_incoming_damage(damageInfo& info) {
    info.damage = int(1.5 * info.damage);
}

QString vulnerablePower::generate_description(){
    description = tr("Receive 50% more damage from Attacks for %1 turns.").arg(amount);
    return description;
}


void vulnerablePower::at_turn_end(game_action&) {
    decrease();
}

QString vulnerablePower::get_story() {
    return (QObject::tr("Vulnerable, invisible cracks in the enemy's armor that the traveler finds with just a glance.\nWhen these fissures are exposed, every strike sinks deeper, as if the wound itself is eager to open."));
}
