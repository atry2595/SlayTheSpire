#ifndef DRINK_POTION_INFO_H
#define DRINK_POTION_INFO_H

#include <vector>

class abstractPotion;
class abstractEntity;

struct drinkPotionInfo {
    abstractPotion* potion = nullptr;
    abstractEntity* player = nullptr;
    std::vector<abstractEntity*> target_list = {};
};


#endif // DRINK_POTION_INFO_H
