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

QString frailPower::get_story() {
    return (QObject::tr("Frail, invisible threads woven around the traveler's body, making their defense more brittle than glass.\nEvery hit they take leaves more of itself behind, as if the body has suddenly forgotten how to be a shield."));
}
