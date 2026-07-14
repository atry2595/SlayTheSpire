#ifndef ATTACK_INFO_H
#define ATTACK_INFO_H
#include <vector>
#include "damage_info.h"
#include "categories/cards.h"

class abstractEntity;


struct attackInfo{
    abstractEntity* attacker = nullptr;
    std::vector<abstractEntity*> target_list;
    int damage = 0;
    attackType attack_type;
};

struct attackResult {
    std::vector<damageResult> results = {};
};

#endif // ATTACK_INFO_H
