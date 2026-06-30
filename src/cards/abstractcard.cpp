#include "abstractcard.h"

abstractCard::abstractCard(QString name_init, QString description_init, int energy_init,
                           bool exhaust_init, bool retain_init,
                           bool  ethereal_init, bool initial_init)
    :base_name(name_init),
    base_description(description_init),
    base_energy(energy_init),
    base_is_exhaust(exhaust_init),
    base_is_retain(retain_init),
    base_is_ethereal(ethereal_init),
    base_is_initial(initial_init)
{
    initial_set();
}

void abstractCard::initial_set(){
    name = base_name;
    description = base_description;
    energy = base_energy;
    is_upgraded = base_is_upgraded;
    is_exhaust = base_is_exhaust;
    is_retain = base_is_retain;
    is_ethereal = base_is_ethereal;
    is_initial = base_is_initial;
}

void abstractCard::combat_reset(){
    initial_set();
}

void abstractCard::turn_reset(){
    turn_lock = false;
}