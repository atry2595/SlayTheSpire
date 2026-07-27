#include "dual_wield.h"
#include "entity/ironclad.h"
#include "cards/cardfactory.h"
#include <QDebug>

dual_wield::dual_wield()
    :abstractSkillCard(tr("Dual Wield"), "", 1, false, false, false, false)
{
    QString s;
    s += tr("Choose an Attack or Power card. Add a copy of that card into your hand.");
    base_description = description = s;
}

QString dual_wield::generate_description(){

    QString s;
    s += tr("Choose an Attack or Power card. Add a copy of that card into your hand.");
    return s;
}

void dual_wield::play(playInfo& play_info){

    ironclad* player = dynamic_cast<ironclad*>(play_info.attacker);

    std::vector<abstractCard*> selectable;
    for (auto* card : player->get_hand_pile()) {
        if (card->get_card_type() == CardType::attack || card->get_card_type() == CardType::power)
            selectable.push_back(card);
    }

    if (selectable.empty()) return;
    emit play_info.actions.get_event()->selectCard(selectable);
    cnt = connect(play_info.actions.get_event(), &combatEvent::cardSelected, this, [=, &play_info](abstractCard* card){

        if (card){
            qDebug() << count;
            for (int i = 0; i<count; i++){
                abstractCard* new_card = CardFactory::createCard(card->get_card_id());
                if (card->get_upgraded()) new_card->upgrade();
                if (card->get_available()) new_card->set_available(true);
                player->hand_pile_add(new_card, true);
            }
        }

        disconnect(cnt);
    });

}

void dual_wield::upgrade(){
    count = 2;
    is_upgraded = true;
    description = generate_description();
}

void dual_wield::base_upgrade(){
    base_count = count = 2;
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}

void dual_wield::combat_reset() {
    abstractCard::combat_reset();
    count = base_count;
}




