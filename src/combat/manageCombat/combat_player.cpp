#include "combat_player.h"
#include "cards/cardfactory.h"
#include "utils/RNG.h"
#include "items/potions/abstractpotion.h"

combat_player::combat_player()
    :character(new ironclad)
{
    energy = base_energy;

    for (auto item : ironclad::starting_deck){
        abstractCard* nc = CardFactory::createCard(item);
        base_deck.push_back(nc);
    }

    deck = base_deck;

}



void combat_player::hand_pile_add(abstractCard* card){
    if (hand_pile.size() < max_hand_card_number)
        hand_pile.push_back(card);
}
void combat_player::hand_pile_remove(abstractCard* card){
    auto it = std::find(hand_pile.begin(), hand_pile.end(), card);
    if (it != hand_pile.end()){
        hand_pile.erase(it);
    }
}



void combat_player::draw_pile_add(abstractCard* card){
    draw_pile.push_back(card);
}
void combat_player::draw_pile_remove(abstractCard* card){
    auto it = std::find(draw_pile.begin(), draw_pile.end(), card);
    if (it != draw_pile.end()){
        draw_pile.erase(it);
    }
}



void combat_player::discard_pile_add(abstractCard* card){
    discard_pile.push_back(card);
}
void combat_player::discard_pile_remove(abstractCard* card){
    auto it = std::find(discard_pile.begin(), discard_pile.end(), card);
    if (it != discard_pile.end()){
        discard_pile.erase(it);
    }
}



void combat_player::exhaust_pile_add(abstractCard* card){
    exhaust_pile.push_back(card);
}
void combat_player::exhaust_pile_remove(abstractCard* card){
    auto it = std::find(exhaust_pile.begin(), exhaust_pile.end(), card);
    if (it != exhaust_pile.end()){
        exhaust_pile.erase(it);
    }
}


void combat_player::base_deck_add(abstractCard* card){
    base_deck.push_back(card);
}
void combat_player::base_deck_remove(abstractCard* card){
    auto it = std::find(base_deck.begin(), base_deck.end(), card);
    if (it != base_deck.end() && card->can_remove_from_deck()){
        delete card;
        base_deck.erase(it);
    }
}


void combat_player::deck_add(abstractCard* card){
    deck.push_back(card);
}
void combat_player::deck_remove(abstractCard* card){
    auto it = std::find(deck.begin(), deck.end(), card);
    if (it != deck.end()){
        deck.erase(it);
    }
}



void combat_player::draw_card(){

    if (draw_pile.empty() && discard_pile.empty()) return;

    if (draw_pile.size() == 0) apply_discard_pile();

    auto card = draw_pile[0];
    draw_pile_remove(card);
    hand_pile_add(card);

    if (draw_pile.size() == 0) apply_discard_pile();
}

void combat_player::apply_discard_pile(){
    shuffle_pile(discard_pile);
    draw_pile.insert(draw_pile.end(), discard_pile.begin(), discard_pile.end());
    discard_pile.clear();
}

void combat_player::shuffle_pile(std::vector<abstractCard*>& pile){
    //QT + media
    //QT + media
    RNG::instance().shuffle(pile);
}

void combat_player::play_card(abstractCard* card) {
    hand_pile_remove(card);

    if (card->get_exhaust()) exhaust_pile_add(card);
    else discard_pile_add(card);
}

void combat_player::at_turn_start() {
    for (int i = 0; i < hand_card_number; i++) draw_card();
}

void combat_player::at_turn_end() {

    for (int i = hand_pile.size() - 1; i >= 0; i++){

        if (hand_pile[i]->get_ethereal()){
            exhaust_pile_add(hand_pile[i]);
            hand_pile_remove(hand_pile[i]);
        }

        else if (hand_pile[i]->get_retain())  {}

        else {
            discard_pile_add(hand_pile[i]);
            hand_pile_remove(hand_pile[i]);
        }

    }

}

void combat_player::at_combat_start(){

    deck = base_deck;

    for (auto item : deck){
        if (item->get_initial()) hand_pile_add(item);
    }
}

void combat_player::at_combat_end() {
    deck.clear();
    hand_pile.clear();
    exhaust_pile.clear();
    draw_pile.clear();
    discard_pile.clear();
}


void combat_player::potion_list_add(abstractPotion* pot){
    if (potion_list.size() < max_potion_number) potion_list.push_back(pot);
}

void combat_player::potion_list_remove(abstractPotion* pot){
    for (int i = 0; i< potion_list.size(); i++){
        if (pot == potion_list[i]){
            potion_list.erase(potion_list.begin() + i);
            delete pot;
            return;
        }
    }
}
