#ifndef COMBATREWARDS_H
#define COMBATREWARDS_H

#include <vector>

class abstractCard;
class abstractPotion;
class abstractRelic;

struct combatReward {
    int returned_coin = 0;
    int coin = 0;
    std::vector<abstractCard*> card = {};
    std::vector<abstractRelic*> relic = {};
    std::vector<abstractPotion*> potion = {};
};

#endif // COMBATREWARDS_H
