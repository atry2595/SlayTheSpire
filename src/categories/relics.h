#ifndef RELICS_H
#define RELICS_H

#include <vector>

enum class relicID{
    burning_blood,

    girya,
    ice_cream,
    shuriken,
    kunai,
    anchor,
    bag_of_marbles,
    happy_flower,
    red_skull,
    preserved_insect,
    vajra,
    oddly_smooth_stone,
    the_boot,
    greenback,
    blood_vial,
    centennial_puzzle,
    horn_cleat,
    gremlin_horn,
    tungsten_rod,
    captains_wheel,

    calling_bell,
    mark_of_pain,
    velvet_choker,
    black_star,
    lively_plant,
    philosophers_stone,
    cursed_key,
    sozu,
    slavers_collar,

    warped_tongs,
    mutagenic_strength,
    cultist_headpiece,
    red_mask,
    helmet_of_the_cleric,
    gremlin_visage,
    golden_idol,
    spirit_poop
};

enum class relicRarity {
    starter,
    common,
    uncommon,
    rare,
    boss,
    shop,
    event,
    special
};

inline const std::vector<relicID> common_relic = {
    relicID::anchor,
    relicID::bag_of_marbles,
    relicID::happy_flower,
    relicID::red_skull,
    relicID::preserved_insect,
    relicID::vajra,
    relicID::oddly_smooth_stone,
    relicID::the_boot,
    relicID::greenback,
    relicID::blood_vial,
    relicID::centennial_puzzle
};

inline const std::vector<relicID> uncommon_relic = {
    relicID::shuriken,
    relicID::kunai,
    relicID::horn_cleat,
    relicID::gremlin_horn
};

inline const std::vector<relicID> rare_relic = {
    relicID::girya,
    relicID::ice_cream,
    relicID::tungsten_rod,
    relicID::captains_wheel,
};

inline const std::vector<relicID> boss_relic = {
    relicID::calling_bell,
    relicID::mark_of_pain,
    relicID::velvet_choker,
    relicID::black_star,
    relicID::lively_plant,
    relicID::philosophers_stone,
    relicID::cursed_key,
    relicID::sozu,
    relicID::slavers_collar
};

#endif // RELICS_H
