#ifndef PLAY_INFO_H
#define PLAY_INFO_H

#include <vector>
#include "game_action.h"

class abstractEntity;
class combat_player;

struct playInfo{
    abstractEntity* attacker = nullptr;
    std::vector<abstractEntity*> target_list = {};
    game_action& actions;

    combat_player* players_data = nullptr;

    playInfo(game_action& a)
        : actions(a) {}
};

#endif // PLAY_INFO_H
