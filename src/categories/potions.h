#ifndef POTIONS_H
#define POTIONS_H

#include <vector>

enum class potionID{
    block_potion,
    fire_potion,
    energy_potion,
    swift_potion,
    fairy_in_a_bottle,
    dexterity_potion,
    explosive_potion,
    fear_potion,
    strength_potion,
    weak_potion,
    white_blood_potion,
    cultist_potion
};

enum class PotionType {
    common,
    uncommon,
    rare
};

const std::vector<potionID> common_potions = {
    potionID::block_potion,
    potionID::fire_potion,
    potionID::energy_potion,
    potionID::swift_potion,
    potionID::dexterity_potion,
    potionID::explosive_potion,
    potionID::fear_potion,
    potionID::strength_potion,
    potionID::weak_potion,
    potionID::white_blood_potion
};

const std::vector<potionID> uncommon_potions = {
    potionID::cultist_potion
};

const std::vector<potionID> rare_potions = {
    potionID::fairy_in_a_bottle
};

#endif // POTIONS_H
