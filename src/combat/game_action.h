#ifndef GAME_ACTION_H
#define GAME_ACTION_H
#include "attack_info.h"
#include "combat_event.h"
#include "damage_info.h"

class game_action
{
    combatEvent* event;
    //combat manager
public:
    game_action(combatEvent* eve);
    void attack(attackInfo& info);
};

#endif // GAME_ACTION_H
