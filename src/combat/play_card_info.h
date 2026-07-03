#ifndef PLAY_CARD_INFO_H
#define PLAY_CARD_INFO_H

#include <vector>

class abstractCard;
class abstractEntity;
class combat_player;

struct playCardInfo {
    abstractCard* card = nullptr;
    abstractEntity* owner = nullptr;
    std::vector<abstractEntity*> target_list = {};

    combat_player* players_data = nullptr;
};


#endif // PLAY_CARD_INFO_H
