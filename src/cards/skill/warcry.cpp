#include "warcry.h"
#include "entity/ironclad.h"

warcry::warcry()
    :abstractSkillCard(tr("warcry"), "", 0, true, false, false, false)
{
    QString s;
    s += tr("Draw %1 card.").arg(count);
    s += tr("\nPut a card from your hand onto the top of your draw pile.");
    if (is_exhaust) s += tr("\nExhaust.");
    base_description = description = s;
}

QString warcry::generate_description(){

    QString s;
    s += tr("Draw %1 card.").arg(count);
    s += tr("\nPut a card from your hand onto the top of your draw pile.");
    if (is_exhaust) s += tr("\nExhaust.");
    return s;
}

void warcry::play(playInfo& play_info){

    ironclad* player = dynamic_cast<ironclad*>(play_info.attacker);

    for (int i = 0; i < count; i++) player->draw_card();

    std::vector<abstractCard*> selectable = player->get_hand_pile();

    abstractCard* card = ironclad::select_card(selectable);

    player->hand_pile_remove(card, true);
    player->draw_pile_add_by_index(card, true, 0);
}

void warcry::upgrade(){
    count = 2;
    is_upgraded = true;
    description = generate_description();
}

void warcry::base_upgrade(){
    base_count = count = 2;
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}

void warcry::combat_reset() {
    abstractCard::combat_reset();
    count = base_count;
}




