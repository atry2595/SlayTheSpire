#include "bludgeon.h"

bludgeon::bludgeon(bool upgraded_init)
    :abstractAttackCard(tr("bludgeon"), "", 3, 32, upgraded_init, false, false, false, false, true)
{
    QString s;
    s += tr("Deal %1 damage.").arg(damage);
    base_description = description = s;
}

QString bludgeon::generate_description(){
    return tr("Deal %1 damage.").arg(damage);
}

void bludgeon::play(){
    emit deal_damage(damage);
}

void bludgeon::upgrade(){
    damage = 42;
    is_upgraded = true;
    emit upgraded();
}

void bludgeon::base_upgrade(){
    base_damage = 42;
    is_upgraded = true;
    base_description = generate_description();

    emit base_upgraded();

    reset();
}




