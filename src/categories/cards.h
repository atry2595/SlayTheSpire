#ifndef CARDS_H
#define CARDS_H

#include <vector>


enum class CardType{
    attack,
    skill,
    power,
    status,
    curse
};

enum class cardID{
    strike,
    reaper,
    bludgeon,
    feed,
    immolate,
    whirlwind,
    blood_for_blood,
    bash,
    twin_strike,
    perfected_strike,
    clash,
    uppercut,
    heavy_blade,
    pommel_strike,
    carnage,
    hemokinesis,

    defend,
    exhume,
    limit_break,
    offering,
    impervious,
    dual_wield,
    entrench,
    warcry,
    true_grit,
    shrug_it_off,
    power_through,
    bloodletting,
    disarm,
    battle_trance,
    spot_weakness,
    rage,
    JAX,

    inflame,
    metallicize,
    demon_form,
    brutality,
    feel_no_pain,
    barricade,
    dark_embrace,
    berserk,

    dazed,
    slimed,
    wound,
    burn,

    curse_of_the_bell,
    regret,
    writhe,
    pain,
    injury,
    shame,
    doubt,

    NULLCARD
};


const std::vector<cardID> rare_cards = {
    cardID::reaper,
    cardID::bludgeon,
    cardID::feed,
    cardID::immolate,
    cardID::whirlwind,

    cardID::exhume,
    cardID::limit_break,
    cardID::offering,
    cardID::impervious,
    cardID::dual_wield,

    cardID::demon_form,
    cardID::brutality,
    cardID::feel_no_pain,
    cardID::barricade,
    cardID::dark_embrace,
    cardID::berserk
};


const std::vector<cardID> non_rare_cards = {
    cardID::strike,
    cardID::blood_for_blood,
    cardID::bash,
    cardID::twin_strike,
    cardID::perfected_strike,
    cardID::clash,
    cardID::uppercut,
    cardID::heavy_blade,
    cardID::pommel_strike,
    cardID::carnage,
    cardID::hemokinesis,

    cardID::defend,
    cardID::entrench,
    cardID::warcry,
    cardID::true_grit,
    cardID::shrug_it_off,
    cardID::power_through,
    cardID::bloodletting,
    cardID::disarm,
    cardID::battle_trance,
    cardID::spot_weakness,
    cardID::rage,
    cardID::JAX,

    cardID::inflame,
    cardID::metallicize
};


const std::vector<cardID> attack_cards = {
    cardID::strike,
    cardID::reaper,
    cardID::bludgeon,
    cardID::feed,
    cardID::immolate,
    cardID::whirlwind,
    cardID::blood_for_blood,
    cardID::bash,
    cardID::twin_strike,
    cardID::perfected_strike,
    cardID::clash,
    cardID::uppercut,
    cardID::heavy_blade,
    cardID::pommel_strike,
    cardID::carnage,
    cardID::hemokinesis
};


const std::vector<cardID> skill_cards = {
    cardID::defend,
    cardID::exhume,
    cardID::limit_break,
    cardID::offering,
    cardID::impervious,
    cardID::dual_wield,
    cardID::entrench,
    cardID::warcry,
    cardID::true_grit,
    cardID::shrug_it_off,
    cardID::power_through,
    cardID::bloodletting,
    cardID::disarm,
    cardID::battle_trance,
    cardID::spot_weakness,
    cardID::rage,
    cardID::JAX
};


const std::vector<cardID> power_cards = {
    cardID::inflame,
    cardID::metallicize,
    cardID::demon_form,
    cardID::brutality,
    cardID::feel_no_pain,
    cardID::barricade,
    cardID::dark_embrace,
    cardID::berserk
};

const std::vector<cardID> status_card = {
    cardID::dazed,
    cardID::slimed,
    cardID::wound,
    cardID::burn
};

const std::vector<cardID> curse_cards = {
    cardID::curse_of_the_bell,
    cardID::regret,
    cardID::writhe,
    cardID::pain,
    cardID::injury,
    cardID::shame,
    cardID::doubt
};

#endif // CARDS_H
