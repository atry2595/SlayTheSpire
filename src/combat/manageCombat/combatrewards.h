#ifndef COMBATREWARDS_H
#define COMBATREWARDS_H

#include <vector>

class abstractCard;
class abstractPotion;
class abstractRelic;

class combatReward {
    int returned_gold = 0;
    int gold = 0;
    std::vector<std::vector<abstractCard*>> cards = {};
    std::vector<abstractRelic*> relic = {};
    std::vector<abstractPotion*> potion = {};

public:

    void add_gold(int amount) { gold += amount; };
    int get_gold() { return gold; }

    void add_ruterned_gold(int amount) { returned_gold += amount; }
    int get_returned_gold() { return returned_gold; }

    void add_cards(std::vector<abstractCard*> card) { cards.push_back(card); }
    auto& get_cards() { return cards; }

    void add_relic(abstractRelic* rlc) { relic.push_back(rlc); }
    auto get_relic() { return relic; }

    void add_potion(abstractPotion* pot) { potion.push_back(pot); }
    auto get_potion() { return potion; }

};


#endif // COMBATREWARDS_H
