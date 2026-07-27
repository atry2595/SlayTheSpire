#include "brutalitypower.h"
#include "entity/ironclad.h"
#include "combat/blocking_info.h"


brutalityPower::brutalityPower(abstractEntity* owner_init, int x)
    : abstractPower(tr("brutality"), owner_init, x, 999, 0, true, 1)
{
    description = tr("At the start of your turn, lose %1 HP and draw %1 cards.").arg(amount);
}


QString brutalityPower::generate_description(){
    description = tr("At the start of your turn, lose %1 HP and draw %1 cards.").arg(amount);
    return description;
}


void brutalityPower::at_turn_start(game_action& actions) {
    damageInfo info;
    info.damage = amount;
    info.attacker = nullptr;
    info.target = owner;
    info.block_active = false;
    info.attack_type = attackType::self;
    actions.apply_damage(info);

    ironclad* player = dynamic_cast<ironclad*>(owner);
    for (int i = 0; i<amount; i++) player->draw_card();
}

QString brutalityPower::get_story() {
    return (QObject::tr("Brutality, a relentless rhythm that slips a fresh card into the traveler's hand with every turn of time.\nThis power turns the passage of seconds into a silent ally, as if time itself feeds on the fight."));
}
