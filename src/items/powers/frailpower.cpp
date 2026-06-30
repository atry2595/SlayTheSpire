#include "frailpower.h"

frailPower::frailPower(abstractEntity* owner_init, int x)
    : abstractPower(tr("Frail"), owner_init, x, 999, 0, false, 2)
{
    description = tr("Gain 25% less Block from cards for %1 turns.").arg(amount);
}

void frailPower::modify_blocking(blockingInfo& info) {
    info.block = int(info.block * 0.75);
}

void frailPower::at_turn_end(game_action&){
    decrease();
}

QString frailPower::generate_description(){
    description = tr("Gain 25% less Block from cards for %1 turns.").arg(amount);
    return description;
}