#ifndef DAMAGE_INFO_H
#define DAMAGE_INFO_H

class abstractEntity;

struct damageInfo{
    abstractEntity* attacker = nullptr;
    abstractEntity* target = nullptr;
    int damage = 0;
};


#endif // DAMAGE_INFO_H
