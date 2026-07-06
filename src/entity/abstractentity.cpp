#include "abstractentity.h"
#include "items/powers/abstractpower.h"
#include "items/relics/abstractrelic.h"
#include <algorithm>
#include "combat/game_action.h"

abstractEntity::abstractEntity(QString name_init, int base_max_hp_init)
    :base_max_hp(base_max_hp_init), name(name_init)
{
    initial_set();
}

void abstractEntity::initial_set(){
    hp = max_hp = base_max_hp;
    block = 0;
}

void abstractEntity::act_reset(){
    hp = max_hp;
    block = 0;
}

void abstractEntity::combat_reset(){    
    block = 0;
    block_reset_in_combat = true;

    for (auto p : powers_list)
        delete p;

    powers_list.clear();

}

void abstractEntity::turn_reset(){
    if (block_reset_in_combat) block = 0;
}

void abstractEntity::add_power(game_action& actions, abstractPower* power){
    for (auto item : powers_list){
        if (item->get_id() == power->get_id()){
            item->increase(power->get_amount());
            delete power;
            return;
        }
    }

    powers_list.push_back(power);
    sort(powers_list.begin(), powers_list.end(), [](abstractPower* p1, abstractPower* p2){
        return p1->get_order() < p2->get_order();
    });

    power->added_time(actions);

}

void abstractEntity::remove_power(abstractPower* power) {
    for (int i = 0; i<powers_list.size(); i++){

        if (powers_list[i] == power) {
            delete powers_list[i];
            powers_list.erase(powers_list.begin() + i);
        }
    }
}

void abstractEntity::remove_power_by_id(powerID power) {
    for (int i = 0; i<powers_list.size(); i++){

        if (powers_list[i]->get_id() == power) {
            delete powers_list[i];
            powers_list.erase(powers_list.begin() + i);
        }
    }
}

abstractPower* abstractEntity::get_spec_power(powerID power){
    for (int i = 0; i<powers_list.size(); i++){

        if (powers_list[i]->get_id() == power) {
            return powers_list[i];
        }
    }

    return nullptr;
}

void abstractEntity::remove_zero_power(){

    for (int i = powers_list.size() - 1; i >= 0 ;i++){
        if (powers_list[i]->get_amount() == 0){
            delete powers_list[i];
            powers_list.erase(powers_list.begin() + i);
        }
    }
}




void abstractEntity::add_relic(game_action& actions, abstractRelic* relic){
    for (auto item : relics_list){
        if (item->get_id() == relic->get_id()){
            delete relic;
            return;
        }
    }

    relics_list.push_back(relic);
    relic->added_time(actions);

}

void abstractEntity::remove_relic(abstractRelic* relic) {
    for (int i = 0; i<relics_list.size(); i++){

        if (relics_list[i] == relic) {
            delete relics_list[i];
            relics_list.erase(relics_list.begin() + i);
        }
    }
}

void abstractEntity::remove_relic_by_id(relicID relic) {
    for (int i = 0; i<relics_list.size(); i++){

        if (relics_list[i]->get_id() == relic) {
            delete relics_list[i];
            relics_list.erase(relics_list.begin() + i);
        }
    }
}

abstractRelic* abstractEntity::get_spec_relic(relicID relic){
    for (int i = 0; i<relics_list.size(); i++){

        if (relics_list[i]->get_id() == relic) {
            return relics_list[i];
        }
    }

    return nullptr;
}



void abstractEntity::modify_attack(attackInfo& info) {
    for (auto item : powers_list){
        item->modify_attack(info);
    }
    for (auto item : relics_list){
        item->modify_attack(info);
    }
    remove_zero_power();
}
void abstractEntity::modify_incoming_damage(damageInfo& info) {
    for (auto item : powers_list){
        item->modify_incoming_damage(info);
    }
    for (auto item : relics_list){
        item->modify_incoming_damage(info);
    }
    remove_zero_power();
}
void abstractEntity::modify_blocking(blockingInfo& info) {
    for (auto item : powers_list){
        item->modify_blocking(info);
    }
    for (auto item : relics_list){
        item->modify_blocking(info);
    }
    remove_zero_power();
}
void abstractEntity::at_turn_start(game_action& info) {
    for (auto item : powers_list){
        item->at_turn_start(info);
    }
    for (auto item : relics_list){
        item->at_turn_start(info);
    }
    remove_zero_power();
}
void abstractEntity::at_turn_end(game_action& info) {
    for (auto item : powers_list){
        item->at_turn_end(info);
    }
    for (auto item : relics_list){
        item->at_turn_end(info);
    }
    remove_zero_power();
}
void abstractEntity::at_combat_start(game_action& info) {
    for (auto item : powers_list){
        item->at_combat_start(info);
    }
    for (auto item : relics_list){
        item->at_combat_start(info);
    }
    remove_zero_power();
}
void abstractEntity::at_combat_end(game_action& info) {
    for (auto item : powers_list){
        item->at_combat_end(info);
    }
    for (auto item : relics_list){
        item->at_combat_end(info);
    }
    remove_zero_power();
}
void abstractEntity::damage_applied(game_action&info) {
    for (auto item : powers_list){
        item->damage_applied(info);
    }
    for (auto item : relics_list){
        item->damage_applied(info);
    }
    remove_zero_power();
}
