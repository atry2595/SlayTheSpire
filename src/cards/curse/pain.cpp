#include "pain.h"

pain::pain()
    :abstractCurseCard(tr("Pain"), "", 0, false, false, false, false)
{
    base_is_playable = playable = false;
    QString s;
    if (!playable) s += tr("Unplayable.\n");
    s+= tr("While in hand, lose 1 HP when other cards are played.");
    base_description = description = s;
}

QString pain::generate_description(){

    QString s;
    if (!playable) s += tr("Unplayable.\n");
    s+= tr("While in hand, lose 1 HP when other cards are played.");
    return s;
}

void pain::play(playInfo& play_info){
}

void pain::upgrade(){
}

void pain::base_upgrade(){
}


void pain::hand_turn_start(playInfo& info) {
    play_card_connection = connect(info.actions.get_event(), &combatEvent::card_played, this,
        [this, &info](playCardInfo& card) {
            if (card.owner == info.attacker){
                damageInfo dmg;
                dmg.damage = 1;
                dmg.attacker = nullptr;
                dmg.target = info.attacker;
                dmg.block_active = false;
                dmg.attack_type = attackType::self;
                info.actions.apply_damage(dmg);
            }
        });
}


void pain::hand_turn_end(playInfo& info) {
    disconnect(play_card_connection);
}




