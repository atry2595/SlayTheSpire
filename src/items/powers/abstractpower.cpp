#include "abstractpower.h"


abstractPower::abstractPower(QString name_init, abstractEntity* owner_init, int x, int max_x, int min_x)
    :name(name_init), owner(owner_init), amount(x), max_amount(max_x), min_amount(min_x)
{

}
