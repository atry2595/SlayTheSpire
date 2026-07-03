#include "true_grit.h"
#include "entity/ironclad.h"
#include "utils/RNG.h"

true_grit::true_grit()
    :abstractSkillCard(tr("True Grit"), "", 1, false, false, false, false)
{
    QString s;
    s += tr("Gain %1 block.").arg(block);
    if (is_upgraded == false) s += tr("\nExhaust 1 card at random.");
    else s += tr("\nExhaust 1 card.");
    base_description = description = s;
}

QString true_grit::generate_description(){

    QString s;
    s += tr("Gain %1 block.").arg(block);
    if (is_upgraded == false) s += tr("\nExhaust 1 card at random.");
    else s += tr("\nExhaust 1 card.");
    return s;
}

void true_grit::play(playInfo& play_info){

    ironclad* player = dynamic_cast<ironclad*>(play_info.attacker);

    blockingInfo bl;
    bl.block = block;
    bl.owner = play_info.attacker;
    play_info.actions.apply_block(bl);

    std::vector<abstractCard*> selectable;
    for (auto item :player->get_hand_pile()){
        if (item != this) selectable.push_back(item);
    }

    if (selectable.empty()) return;

    abstractCard* card;
    if (random_select) card = RNG::instance().choice(selectable);
    else card = ironclad::select_card(selectable);

    player->hand_pile_remove(card, true);
    player->exhaust_pile_add(card);
}

void true_grit::upgrade(){
    block = 9;
    random_select = false;
    is_upgraded = true;
    description = generate_description();
}

void true_grit::base_upgrade(){
    base_block = block = 9;
    base_random_select = random_select = false;
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}

void true_grit::combat_reset() {
    abstractCard::combat_reset();
    block = base_block;
    random_select = base_random_select;
}




