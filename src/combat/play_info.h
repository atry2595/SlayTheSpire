#ifndef PLAY_INFO_H
#define PLAY_INFO_H

#include <vector>
#include "game_action.h"

class Entity;

struct playInfo{
    Entity* attacker;
    std::vector<Entity*> target_list;
    game_action& actions;
};

#endif // PLAY_INFO_H
