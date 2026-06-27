#include "abstractcard.h"

abstractCard::abstractCard(QString name_init, QString description_init, CardType type_init, int energy_init,
                           bool upgrated_init, bool exhaust_init, bool retain_init, bool  ethereal_init, bool initial_init)
    :base_name(name_init),
    base_description(description_init),
    base_type(type_init),
    base_energy(energy_init),
    base_upgrated(upgrated_init),
    base_exhaust(exhaust_init),
    base_retain(retain_init),
    base_ethereal(ethereal_init),
    base_initial(initial_init)
{
    init();
}

void abstractCard::init(){
    name = base_name;
    description = base_description;
    type = base_type;
    energy = base_energy;
    lock = false;
    upgrated = base_upgrated;
    exhaust = base_exhaust;
    retain = base_retain;
    ethereal = base_ethereal;
    initial = base_ethereal;
}

void abstractCard::reset(){
    init();
}
