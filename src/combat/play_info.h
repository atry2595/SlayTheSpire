#ifndef PLAY_INFO_H
#define PLAY_INFO_H

#include <vector>
#include "game_action.h"

class abstractEntity;

struct playInfo{
    abstractEntity* attacker = nullptr;
    std::vector<abstractEntity*> target_list = {};
    game_action& actions;

    playInfo(game_action& a)
        : actions(a) {}
};

#endif // PLAY_INFO_H
