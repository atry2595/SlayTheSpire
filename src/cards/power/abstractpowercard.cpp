#include "abstractpowercard.h"


abstractPowerCard::abstractPowerCard(QString name_init, QString description_init, int energy_init,
                                     bool exhaust_init, bool retain_init, bool  ethereal_init, bool initial_init)
    :abstractCard(name_init, description_init, energy_init, exhaust_init, retain_init, ethereal_init, initial_init)
{}