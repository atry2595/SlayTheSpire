#ifndef COMBAT_PLAYER_H
#define COMBAT_PLAYER_H

#include <QObject>
#include <vector>
#include "entity/ironclad.h"
#include "cards/abstractcard.h"

class abstractRelic;
class abstractPotion;

class combat_player : public QObject
{
    Q_OBJECT

protected:
    ironclad* character;
    int base_energy = 3;
    int hand_card_number = 5;
    int energy;

    const int max_potion_number = 3;
    const int max_hand_card_number = 10;

    std::vector<abstractCard*> base_deck;
    std::vector<abstractCard*> deck;
    std::vector<abstractPotion*> potion_list;
    std::vector<abstractRelic*> relic_list;

    std::vector<abstractCard*> hand_pile;
    std::vector<abstractCard*> discard_pile;
    std::vector<abstractCard*> draw_pile;
    std::vector<abstractCard*> exhaust_pile;

public:
    combat_player();

    ironclad* get_character() { return character; }
    int get_base_energy() { return base_energy; }
    int get_energy() { return energy; }

    std::vector<abstractCard*>& get_deck() { return deck; }
    std::vector<abstractPotion*>& get_potion_list() { return potion_list; }
    std::vector<abstractRelic*>& get_relic_list() { return relic_list; }

    std::vector<abstractCard*>& get_hand_pile() { return hand_pile; }
    std::vector<abstractCard*>& get_discard_pile() { return discard_pile; }
    std::vector<abstractCard*>& get_draw_pile() { return draw_pile; }
    std::vector<abstractCard*>& get_exhaust_pile() { return exhaust_pile; }

    void set_base_energy(int i_init) { base_energy = i_init; }
    void set_energy(int i_init) {energy = i_init; }

    void hand_pile_add(abstractCard* card);
    void hand_pile_remove(abstractCard* card);

    void draw_pile_add(abstractCard* card);
    void draw_pile_remove(abstractCard* card);

    void discard_pile_add(abstractCard* card);
    void discard_pile_remove(abstractCard* card);

    void exhaust_pile_add(abstractCard* card);
    void exhaust_pile_remove(abstractCard* card);

    void base_deck_add(abstractCard* card);
    void base_deck_remove(abstractCard* card);

    void deck_add(abstractCard* card);
    void deck_remove(abstractCard* card);

    void draw_card();
    void apply_discard_pile();
    void shuffle_pile(std::vector<abstractCard*>& pile);
    void play_card(abstractCard* card);

    void at_turn_start();
    void at_turn_end();

    void at_combat_start();
    void at_combat_end();

};

#endif // COMBAT_PLAYER_H
