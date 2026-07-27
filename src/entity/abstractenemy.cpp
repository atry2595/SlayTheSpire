#include "abstractenemy.h"

abstractEnemy::abstractEnemy(QString name_init, int base_max_hp_init)
    :abstractEntity(name_init, base_max_hp_init)
{}

void abstractEnemy::perform_attack(playInfo& info){
    enemy_intent& intnt = intent_list.at(current_move);

    attackInfo atck_info;
    atck_info.attacker = info.attacker;
    atck_info.target_list = info.target_list;
    atck_info.damage = intnt.damage;
    atck_info.attack_type = attackType::intent;

    for (int i = 0 ; i<intnt.repeat; i++) {
        info.actions.attack(atck_info);
    }
}

void abstractEnemy::perform_block(playInfo& info, int block_number){
    blockingInfo bl;
    bl.block = block_number;
    bl.owner = info.attacker;
    info.actions.apply_block(bl);
}
