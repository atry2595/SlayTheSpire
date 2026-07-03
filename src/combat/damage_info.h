#ifndef DAMAGE_INFO_H
#define DAMAGE_INFO_H

class abstractEntity;

struct damageInfo{
    abstractEntity* attacker = nullptr;
    abstractEntity* target = nullptr;
    int damage = 0;
};

struct damageResult {
    int final_damage = 0;
    int blocked = 0;
    bool killed = false;
};

#endif // DAMAGE_INFO_H
