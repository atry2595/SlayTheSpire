#include "exhume.h"
#include "entity/ironclad.h"

exhume::exhume()
    :abstractSkillCard(tr("Exhume"), "", 1, true, false, false, false)
{
    QString s;
    s += tr("Put a card from your Exhaust pile into your hand.");
    if (is_exhaust) s += tr("\nExhaust.");
    base_description = description = s;
}

QString exhume::generate_description(){

    QString s;
    s += tr("Put a card from your Exhaust pile into your hand.");
    if (is_exhaust) s += tr("\nExhaust.");
    return s;
}

void exhume::play(playInfo& play_info){

    ironclad* player = dynamic_cast<ironclad*>(play_info.attacker);

    std::vector<abstractCard*> selectable;
    for (auto* card : player->get_exhaust_pile()) {
        if (card->get_card_id() != cardID::exhume)
            selectable.push_back(card);
    }

    if (selectable.empty()) return;
    emit play_info.actions.get_event()->selectCard(selectable);
    cnt = connect(play_info.actions.get_event(), &combatEvent::cardSelected, this, [=, &play_info](abstractCard* card){

        if (card){
            card->set_available(player->get_energy() >= card->get_energy());
            player->exhaust_pile_remove(card, true);
            player->hand_pile_add(card, true);
            playInfo inf(play_info.actions);
        }
        disconnect(cnt);

    });

}

void exhume::upgrade(){
    energy = 0;
    is_upgraded = true;
    description = generate_description();
}

void exhume::base_upgrade(){
    base_energy = energy = 0;
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}

void exhume::combat_reset() {
    abstractCard::combat_reset();
}




