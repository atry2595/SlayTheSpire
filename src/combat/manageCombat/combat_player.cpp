#include "combat_player.h"
#include "cards/cardfactory.h"
#include "utils/RNG.h"
#include "items/potions/abstractpotion.h"
#include "categories/general.h"

combat_player::combat_player(combatEvent* eve)
    :character(new ironclad),
    event(eve)
{
    energy = base_energy;

    for (auto item : ironclad::starting_deck){
        abstractCard* nc = CardFactory::createCard(item);
        deck.push_back(nc);
    }
}



void combat_player::hand_pile_add(abstractCard* card, bool independent){
    if (hand_pile.size() < max_hand_card_number){
        hand_pile.push_back(card);
    }
    if (independent) emit event->card_moved(card, PileType::none, PileType::hand);
}



void combat_player::hand_pile_remove(abstractCard* card, bool independent){
    auto it = std::find(hand_pile.begin(), hand_pile.end(), card);
    if (it != hand_pile.end()){
        hand_pile.erase(it);
    }

    if (independent) emit event->card_moved(card, PileType::hand, PileType::none);
}



void combat_player::draw_pile_add(abstractCard* card, bool independent){
    draw_pile.push_back(card);
    if (independent) emit event->card_moved(card, PileType::none, PileType::draw);
}



void combat_player::draw_pile_remove(abstractCard* card, bool independent){
    auto it = std::find(draw_pile.begin(), draw_pile.end(), card);
    if (it != draw_pile.end()){
        draw_pile.erase(it);
    }
    if (independent) emit event->card_moved(card, PileType::draw, PileType::none);
}



void combat_player::discard_pile_add(abstractCard* card, bool independent){
    discard_pile.push_back(card);
    if (independent) emit event->card_moved(card, PileType::none, PileType::discard);
}



void combat_player::discard_pile_remove(abstractCard* card, bool independent){
    auto it = std::find(discard_pile.begin(), discard_pile.end(), card);
    if (it != discard_pile.end()){
        discard_pile.erase(it);
    }
    if (independent) emit event->card_moved(card, PileType::discard, PileType::none);
}



void combat_player::exhaust_pile_add(abstractCard* card, bool independent){
    exhaust_pile.push_back(card);
    if (independent) emit event->card_moved(card, PileType::none, PileType::exhaust);
}



void combat_player::exhaust_pile_remove(abstractCard* card, bool independent){
    auto it = std::find(exhaust_pile.begin(), exhaust_pile.end(), card);
    if (it != exhaust_pile.end()){
        exhaust_pile.erase(it);
    }
    if (independent) emit event->card_moved(card, PileType::exhaust, PileType::none);
}



void combat_player::deck_add(abstractCard* card){
    deck.push_back(card);
}



void combat_player::deck_remove(abstractCard* card){
    if (card->can_remove_from_deck() == false) return;

    auto it = std::find(deck.begin(), deck.end(), card);
    if (it != deck.end()){
        delete card;
        deck.erase(it);
    }
}



void combat_player::draw_card(){

    if (draw_pile.empty() && discard_pile.empty()) return;

    if (draw_pile.size() == 0) apply_discard_pile();

    auto card = draw_pile[0];
    draw_pile_remove(card);
    hand_pile_add(card);
    emit event->card_moved(card, PileType::draw, PileType::hand);

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
    emit event->draw_pile_shuffled();
}



void combat_player::play_card(playCardInfo& info) {
    if (energy < info.card->get_energy()) return;

    game_action actions(event);
    info.owner = character;
    actions.play_card(info);

    energy -= info.card->get_energy();

    hand_pile_remove(info.card);

    if (info.card->get_exhaust()) {
        exhaust_pile_add(info.card);
        emit event->card_moved(info.card, PileType::hand, PileType::exhaust);
    }
    else {
        discard_pile_add(info.card);
        emit event->card_moved(info.card, PileType::hand, PileType::discard);
    }

    for (auto item : hand_pile){
        item->update_by_energy(energy);
    }
}



void combat_player::at_turn_start() {
    energy = base_energy;

    for (auto item : hand_pile){
        item->update_by_energy(energy);
    }

    for (int i = 0; i < hand_card_number; i++) draw_card();
}



void combat_player::at_turn_end() {

    for (int i = hand_pile.size() - 1; i >= 0; i++){

        hand_pile[i]->turn_reset();

        if (hand_pile[i]->get_ethereal()){
            exhaust_pile_add(hand_pile[i]);
            emit event->card_moved(hand_pile[i], PileType::hand, PileType::exhaust);
            hand_pile_remove(hand_pile[i]);
        }

        else if (hand_pile[i]->get_retain())  {}

        else {
            discard_pile_add(hand_pile[i]);
            emit event->card_moved(hand_pile[i], PileType::hand, PileType::discard);
            hand_pile_remove(hand_pile[i]);
        }

    }

}



void combat_player::at_combat_start(){

    draw_pile = deck;

    for (auto item : draw_pile){
        if (item->get_initial()) {
            hand_pile_add(item);
            emit event->card_moved(item, PileType::draw, PileType::hand);
        }
    }
    for (auto item : hand_pile){
        draw_pile_remove(item);
    }
}



void combat_player::at_combat_end() {

    for (auto card: deck){
        card->combat_reset();
    }

    hand_pile.clear();
    exhaust_pile.clear();
    draw_pile.clear();
    discard_pile.clear();
}



void combat_player::potion_list_add(abstractPotion* pot){
    if (potion_list.size() < max_potion_number) {
        potion_list.push_back(pot);
        emit event->potion_added(pot);
    }
}



void combat_player::potion_list_remove(abstractPotion* pot){
    for (int i = 0; i< potion_list.size(); i++){
        if (pot == potion_list[i]){
            potion_list.erase(potion_list.begin() + i);
            emit event->potion_removed(pot);
            delete pot;
            return;
        }
    }
}