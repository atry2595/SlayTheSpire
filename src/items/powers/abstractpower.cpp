#include "abstractpower.h"


abstractPower::abstractPower(QString name_init, abstractEntity* owner_init, int x, int max_x, int min_x, bool buff_init, int priority_init)
    :name(name_init), owner(owner_init), amount(x), max_amount(max_x), min_amount(min_x), is_buff(buff_init), priority_order(priority_init)
{
}

void abstractPower::increase(int value){
    if (value >= 0) amount = std::min(amount + value, max_amount);
    else decrease(-value);
    generate_description();
}

void abstractPower::decrease(int value){
    if (value >= 0) amount = std::max(amount - value, min_amount);
    else increase(-value);
    generate_description();
}