#ifndef GAME_ACTION_H
#define GAME_ACTION_H
#include "attack_info.h"
#include "combat_event.h"
#include "damage_info.h"
#include "entity/abstractentity.h"

class game_action
{
    combatEvet* event;
    //combat manager
public:
    game_action(combatEvet* eve);
    void attack(attackInfo& info);
};

#endif // GAME_ACTION_H
