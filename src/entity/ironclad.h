#ifndef IRONCLAD_H
#define IRONCLAD_H

#include <vector>
#include "abstractentity.h"
#include "cards/abstractcard.h"
#include "categories/relics.h"
#include "combat/play_card_info.h"
#include "combat/drink_potion_info.h"

class abstractPotion;
class abstractRelic;

class ironclad : public abstractEntity
{
    Q_OBJECT

    static const std::vector<cardID> starting_deck;
    static constexpr relicID starting_relic = relicID::burning_blood;
    static constexpr int starting_gold = 99;

    combatEvent* event;

protected:
    int base_energy = 3;
    int hand_card_number = 5;
    int energy;

    int max_draw_card = 100;
    int draw_count = 0;

    const int max_potion_number = 3;
    const int max_hand_card_number = 10;

    std::vector<abstractCard*> deck;
    std::vector<abstractCard*> combat_deck;
    std::vector<abstractPotion*> potion_list;
    std::vector<abstractRelic*> relic_list;

    std::vector<abstractCard*> hand_pile;
    std::vector<abstractCard*> discard_pile;
    std::vector<abstractCard*> draw_pile;
    std::vector<abstractCard*> exhaust_pile;

public:
    static abstractCard* select_card(const std::vector<abstractCard*>&);

    entityType get_type() override { return entityType::player; }
    entityID get_ID() override { return entityID::ironclad; }


    ironclad(combatEvent* eve);

    int get_base_energy() { return base_energy; }
    int get_energy() { return energy; }

    std::vector<abstractCard*>& get_deck() { return deck; }
    std::vector<abstractCard*>& get_combat_deck() { return combat_deck; }
    std::vector<abstractPotion*>& get_potion_list() { return potion_list; }
    std::vector<abstractRelic*>& get_relic_list() { return relic_list; }

    std::vector<abstractCard*>& get_hand_pile() { return hand_pile; }
    std::vector<abstractCard*>& get_discard_pile() { return discard_pile; }
    std::vector<abstractCard*>& get_draw_pile() { return draw_pile; }
    std::vector<abstractCard*>& get_exhaust_pile() { return exhaust_pile; }

    void lock_draw_card() { draw_count = max_draw_card;}

    void set_base_energy(int i_init) { base_energy = i_init; }
    void set_energy(int i_init) {energy = i_init; }

    void combat_deck_add(abstractCard* card);
    void combat_deck_remove(abstractCard* card);

    void hand_pile_add(abstractCard* card, bool independent = false);
    void hand_pile_remove(abstractCard* card, bool independent = false);

    void draw_pile_add(abstractCard* card, bool independent = false);
    void draw_pile_add_by_index(abstractCard* card, bool independent = false, int index = 0);
    void draw_pile_remove(abstractCard* card, bool independent = false);

    void discard_pile_add(abstractCard* card, bool independent = false);
    void discard_pile_remove(abstractCard* card, bool independent = false);

    void exhaust_pile_add(abstractCard* card, bool independent = false);
    void exhaust_pile_remove(abstractCard* card, bool independent = false);

    void deck_add(abstractCard* card);
    void deck_remove(abstractCard* card);

    void draw_card();
    void apply_discard_pile();
    void shuffle_pile(std::vector<abstractCard*>& pile);
    void play_card(playCardInfo& info);
    void consume_all_energy();

    void at_turn_start(game_action&) override;
    void at_turn_end(game_action&) override;
    void at_combat_start(game_action&) override;
    void at_combat_end(game_action&) override;
    void damage_applied(game_action&) override;

    void potion_list_add(abstractPotion*);
    void potion_list_remove(abstractPotion*);
};


#endif // IRONCLAD_H
