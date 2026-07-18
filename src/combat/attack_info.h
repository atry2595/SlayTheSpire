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
    cardID card_id = cardID::NULLCARD;
};

struct attackResult {
    attackInfo& info;
    std::vector<damageResult> results = {};

    inline attackResult(attackInfo& inf) : info(inf){}
};

#endif // ATTACK_INFO_H
