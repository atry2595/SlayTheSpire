#ifndef DAMAGE_INFO_H
#define DAMAGE_INFO_H

class abstractEntity;

enum class attackType {
    card,
    relic,
    potion,
    intent,
    power,
    self
};

struct damageInfo{
    abstractEntity* attacker = nullptr;
    abstractEntity* target = nullptr;
    int damage = 0;
    bool block_active = true;
    attackType attack_type;
};

struct damageResult {
    abstractEntity* attacker = nullptr;
    abstractEntity* target = nullptr;
    int final_damage = 0;
    int blocked = 0;
    bool killed = false;
};

#endif // DAMAGE_INFO_H
