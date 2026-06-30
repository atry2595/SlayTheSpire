#include "abstractpotion.h"

abstractPotion::abstractPotion(QString name_init, QString desc_init, abstractEntity* owner_init)
    : name(name_init),
    description(desc_init),
    owner(owner_init)
{}
