#include "abstractentity.h"

abstractEntity::abstractEntity(QString name_init, int base_max_hp_init)
    :base_max_hp(base_max_hp_init), name(name_init)
{
    initial_set();
}

void abstractEntity::initial_set(){
    hp = max_hp = base_max_hp;
    block = 0;
}

void abstractEntity::reset(){
    hp = max_hp;
    block = 0;
}

