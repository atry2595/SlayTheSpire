#include "abstractentity.h"
#include "items/powers/abstractpower.h"
#include <algorithm>

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
    powers_list.clear();
    block = 0;
}

void abstractEntity::add_power(abstractPower* power){
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