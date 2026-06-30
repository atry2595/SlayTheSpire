#ifndef PLAY_INFO_H
#define PLAY_INFO_H

#include <vector>
#include "game_action.h"

class abstractEntity;

struct playInfo{
    abstractEntity* attacker;
    std::vector<abstractEntity*> target_list;
    game_action& actions;
};

#endif // PLAY_INFO_H
