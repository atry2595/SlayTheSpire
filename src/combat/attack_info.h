#ifndef ATTACK_INFO_H
#define ATTACK_INFO_H
#include <vector>
class abstractEntity;

struct attackInfo{
    abstractEntity* attacker = nullptr;
    std::vector<abstractEntity*> target_list;
    int damage = 0;
};

#endif // ATTACK_INFO_H
