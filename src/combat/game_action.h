#ifndef GAME_ACTION_H
#define GAME_ACTION_H
#include "attack_info.h"
#include "combat_event.h"
#include "damage_info.h"
#include "blocking_info.h"
#include "drink_potion_info.h"
#include "play_card_info.h"

class game_action
{
    combatEvent* event;
    //combat manager
public:
    game_action(combatEvent* eve);
    attackResult attack(attackInfo& info);
    damageResult apply_damage(damageInfo& info);
    combatEvent* get_event() {return event;}
    void apply_block(blockingInfo& info);
    void play_card(playCardInfo& info);
    void drink_potion(drinkPotionInfo& info);
    void heal(healInfo& info);
};

#endif // GAME_ACTION_H
