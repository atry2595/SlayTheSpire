#include "regret.h"
#include "entity/ironclad.h"

regret::regret()
    :abstractCurseCard(tr("Regret"), "", 0, false, false, false, false)
{
    base_is_playable = playable = false;
    QString s;
    if (!playable) s += tr("Unplayable.\n");
    s+= tr("At the end of your turn, lose HP equal to the number of cards in your hand.");
    base_description = description = s;
}

QString regret::generate_description(){

    QString s;
    if (!playable) s += tr("Unplayable.\n");
    s+= tr("At the end of your turn, lose HP equal to the number of cards in your hand.");
    return s;
}

void regret::play(playInfo& play_info){
    ironclad* player = dynamic_cast<ironclad*>(play_info.attacker);
    int dmg = player->get_hand_pile().size();

    damageInfo inf;
    inf.damage = dmg;
    inf.attacker = nullptr;
    inf.block_active = false;
    inf.target = play_info.attacker;

    play_info.actions.apply_damage(inf);

}

void regret::upgrade(){
}

void regret::base_upgrade(){
}


void regret::hand_turn_end(playInfo& info){
    play(info);
}




