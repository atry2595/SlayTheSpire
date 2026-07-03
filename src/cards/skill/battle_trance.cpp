#include "battle_trance.h"
#include "entity/ironclad.h"

battle_trance::battle_trance()
    :abstractSkillCard(tr("Battle Trance"), "", 0, false, false, false, false)
{
    QString s;
    s += tr("Draw %1 cards.").arg(count);
    s += tr("\nYou cannot draw additional cards this turn.");
    base_description = description = s;
}

QString battle_trance::generate_description(){

    QString s;
    s += tr("Draw %1 card.").arg(count);
    s += tr("\nYou cannot draw additional cards this turn.");
    return s;
}

void battle_trance::play(playInfo& play_info){

    ironclad* player = dynamic_cast<ironclad*>(play_info.attacker);

    for (int i = 0; i<count; i++)player->draw_card();

    player->lock_draw_card();
}

void battle_trance::upgrade(){
    count = 4;
    is_upgraded = true;
    description = generate_description();
}

void battle_trance::base_upgrade(){
    base_count = count = 4;
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}

void battle_trance::combat_reset() {
    abstractCard::combat_reset();
    count = base_count;
}




