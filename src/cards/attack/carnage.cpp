#include "carnage.h"

carnage::carnage(bool upgraded_init)
    :abstractAttackCard(tr("carnage"), "", 1, 20, upgraded_init, false, false, true, false)
{
    QString s;
    s += tr("Deal %1 damage.").arg(damage);
    if (is_exhaust) s += tr("\nExhaust");
    if (is_retain) s += tr("\nRetain");
    if (is_ethereal) s += tr("\nEthereal");
    if (is_initial) s += tr("\nInitial");

    base_description = description = s;
}

QString carnage::generate_description(){
    QString s;
    s += tr("Deal %1 damage.").arg(damage);
    if (is_exhaust) s += tr("\nExhaust");
    if (is_retain) s += tr("\nRetain");
    if (is_ethereal) s += tr("\nEthereal");
    if (is_initial) s += tr("\nInitial");

    return s;
}

void carnage::play(){
    emit deal_damage(damage);
}

void carnage::upgrade(){
    damage = 28;
    is_upgraded = true;
    emit upgraded();
}

void carnage::base_upgrade(){
    base_damage = 28;
    is_upgraded = true;
    base_description = generate_description();

    emit base_upgraded();

    reset();
}