#ifndef ATTACK_INFO_H
#define ATTACK_INFO_H
#include <vector>
class Entity;

struct attackInfo{
    Entity* attacker;
    std::vector<Entity*> target_list;
    int damage = 0;
};

#endif // ATTACK_INFO_H
