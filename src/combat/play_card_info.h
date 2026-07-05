#ifndef PLAY_CARD_INFO_H
#define PLAY_CARD_INFO_H

#include <vector>

class abstractCard;
class abstractEntity;

struct playCardInfo {
    abstractCard* card = nullptr;
    abstractEntity* owner = nullptr;
    std::vector<abstractEntity*> target_list = {};
};


#endif // PLAY_CARD_INFO_H
