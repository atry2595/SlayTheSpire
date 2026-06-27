#include "abstractcard.h"

abstractCard::abstractCard(QString name_init, QString description_init, CardType type_init, int energy_init,
                           bool upgraded_init, bool exhaust_init, bool retain_init, bool  ethereal_init, bool initial_init, bool rare_init)
    :base_name(name_init),
    base_description(description_init),
    base_type(type_init),
    base_energy(energy_init),
    base_is_upgraded(upgraded_init),
    base_is_exhaust(exhaust_init),
    base_is_retain(retain_init),
    base_is_ethereal(ethereal_init),
    base_is_initial(initial_init),
    is_rare(rare_init)
{
    init();
}

void abstractCard::init(){
    name = base_name;
    description = base_description;
    type = base_type;
    energy = base_energy;
    lock = false;
    is_upgraded = base_is_upgraded;
    is_exhaust = base_is_exhaust;
    is_retain = base_is_retain;
    is_ethereal = base_is_ethereal;
    is_initial = base_is_ethereal;
}

void abstractCard::reset(){
    init();
}
