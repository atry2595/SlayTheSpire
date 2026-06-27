#include "strike.h"

strike::strike(bool upgraded_init)
    :abstractAttackCard(tr("strike"), "", 1, 6, upgraded_init, false, false, false, false)
{
    QString s;
    s += tr("Deal %1 damage.").arg(damage);
    base_description = description = s;
}

QString strike::generate_description(){
    return tr("Deal %1 damage.").arg(damage);
}

void strike::play(){
    emit deal_damage(damage);
}

void strike::upgrade(){
    damage = 9;
    is_upgraded = true;
    emit upgraded();
}

void strike::base_upgrade(){
    base_damage = 9;
    is_upgraded = true;
    base_description = generate_description();

    emit base_upgraded();

    reset();
}




