#ifndef DAMAGE_INFO_H
#define DAMAGE_INFO_H

class Entity;

struct damageInfo{
    Entity* attacker;
    Entity* target;
    int damage = 0;
};


#endif // DAMAGE_INFO_H
