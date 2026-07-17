#include "ironclad.h"
#include "cards/cardfactory.h"
#include "cards/cardfactory.h"
#include "utils/RNG.h"
#include "items/potions/abstractpotion.h"
#include "categories/general.h"
#include "items/relics/relicfactory.h"

const std::vector<cardID> ironclad::starting_deck =
    {cardID::whirlwind,
     cardID::offering, cardID::strike, cardID::whirlwind, cardID::pommel_strike, cardID::bash};

abstractCard* ironclad::select_card(
    const std::vector<abstractCard*>& cards
    )
{
    return nullptr;
}


abstractCard* ironclad::transformCard(abstractCard* selected_card) {

    if (selected_card->get_card_type() == CardType::curse) {
        auto copy_cards = curse_cards;
        auto rsc = RNG::instance().choice(copy_cards);
        return CardFactory::createCard(rsc);
    }


    else if (selected_card->is_rare()) {
        std::vector<double> weight;
        std::vector<cardID> cards;

        for (auto item : non_rare_cards) {
            cards.push_back(item);
            weight.push_back(1);
        }
        for (auto item : rare_cards) {
            cards.push_back(item);
            weight.push_back(3);
        }

        auto rsc = RNG::instance().weighted_choice(cards, weight);

        auto res = CardFactory::createCard(rsc);

        if (selected_card->get_upgraded() && RNG::instance().chance(0.75))
            res->base_upgrade();

        return res;
    }


    else {
        std::vector<double> weight;
        std::vector<cardID> cards;

        for (auto item : non_rare_cards) {
            cards.push_back(item);
            weight.push_back(2);
        }
        for (auto item : rare_cards) {
            cards.push_back(item);
            weight.push_back(1);
        }
        auto rsc = RNG::instance().weighted_choice(cards, weight);

        auto res = CardFactory::createCard(rsc);

        if (selected_card->get_upgraded() && RNG::instance().chance(0.80))
            res->base_upgrade();

        return res;
    }
}



ironclad::~ironclad(){
    combat_deck_remove_unique();
    for (auto* item : deck){
        delete item;
    }
    for (auto* item : potion_list){
        delete item;
    }
}

ironclad::ironclad(combatEvent* eve)
    :abstractEntity(tr("Ironclad"), 80),
    event(eve)
{
    energy = base_energy;
    for (auto item : ironclad::starting_deck){
        abstractCard* nc = CardFactory::createCard(item);
        deck.push_back(nc);
    }
    gold = starting_gold;

    game_action actions(event);
    add_relic(actions, RelicFactory::createRelic(ironclad::starting_relic, this));
}


void ironclad::combat_deck_add(abstractCard* card){
    for (auto item : combat_deck){
        if (item == card) return;
    }

    combat_deck.push_back(card);
}
void ironclad::combat_deck_remove(abstractCard* card){
    auto it = std::find(combat_deck.begin(), combat_deck.end(), card);
    if (it != combat_deck.end()){
        combat_deck.erase(it);
    }
}
void ironclad::combat_deck_remove_unique(){
    for (auto item : combat_deck){
        auto it = std::find(deck.begin(), deck.end(), item);
        if (it == deck.end())delete item;
    }
}


void ironclad::hand_pile_add(abstractCard* card, bool independent){
    if (hand_pile.size() < max_hand_card_number){
        hand_pile.push_back(card);
    }
    combat_deck_add(card);
    if (independent) {
        playCardInfo c_info;
        c_info.card = card;
        c_info.owner = this;
        emit event->card_moved(c_info, PileType::none, PileType::hand);
    }
}
void ironclad::hand_pile_remove(abstractCard* card, bool independent){
    auto it = std::find(hand_pile.begin(), hand_pile.end(), card);
    if (it != hand_pile.end()){
        hand_pile.erase(it);
    }
    playCardInfo c_info;
    c_info.card = card;
    c_info.owner = this;
    if (independent) emit event->card_moved(c_info, PileType::hand, PileType::none);
}


void ironclad::draw_pile_add(abstractCard* card, bool independent){
    draw_pile.push_back(card);
    combat_deck_add(card);
    if (independent) {
        playCardInfo c_info;
        c_info.card = card;
        c_info.owner = this;
        emit event->card_moved(c_info, PileType::none, PileType::draw);
    }
}

void ironclad::draw_pile_add_by_index(abstractCard* card, bool independent, int index ){
    if (index > draw_pile.size()) index = draw_pile.size();
    if (index < 0) index = 0;

    draw_pile.insert(draw_pile.begin() + index, card);
    combat_deck_add(card);
    if (independent) {
        playCardInfo c_info;
        c_info.card = card;
        c_info.owner = this;
        emit event->card_moved(c_info, PileType::none, PileType::draw);
    }
}
void ironclad::draw_pile_remove(abstractCard* card, bool independent){
    auto it = std::find(draw_pile.begin(), draw_pile.end(), card);
    if (it != draw_pile.end()){
        draw_pile.erase(it);
    }
    playCardInfo c_info;
    c_info.card = card;
    c_info.owner = this;
    if (independent) emit event->card_moved(c_info, PileType::draw, PileType::none);
}


void ironclad::discard_pile_add(abstractCard* card, bool independent){
    discard_pile.push_back(card);
    combat_deck_add(card);
    if (independent) {
        playCardInfo c_info;
        c_info.card = card;
        c_info.owner = this;
        emit event->card_moved(c_info, PileType::none, PileType::discard);
    }
}
void ironclad::discard_pile_remove(abstractCard* card, bool independent){
    auto it = std::find(discard_pile.begin(), discard_pile.end(), card);
    if (it != discard_pile.end()){
        discard_pile.erase(it);
    }
    playCardInfo c_info;
    c_info.card = card;
    c_info.owner = this;
    if (independent) emit event->card_moved(c_info, PileType::discard, PileType::none);
}


void ironclad::exhaust_pile_add(abstractCard* card, bool independent){
    exhaust_pile.push_back(card);
    combat_deck_add(card);
    if (independent) {
        playCardInfo c_info;
        c_info.card = card;
        c_info.owner = this;
        emit event->card_moved(c_info, PileType::none, PileType::exhaust);
    }
}
void ironclad::exhaust_pile_remove(abstractCard* card, bool independent){
    auto it = std::find(exhaust_pile.begin(), exhaust_pile.end(), card);
    if (it != exhaust_pile.end()){
        exhaust_pile.erase(it);
    }
    playCardInfo c_info;
    c_info.card = card;
    c_info.owner = this;
    if (independent) emit event->card_moved(c_info, PileType::exhaust, PileType::none);
}


void ironclad::deck_add(abstractCard* card){
    deck.push_back(card);
    combat_deck_add(card);
}
void ironclad::deck_remove(abstractCard* card){
    if (card->can_remove_from_deck() == false) return;

    auto it = std::find(deck.begin(), deck.end(), card);
    if (it != deck.end()){
        delete card;
        deck.erase(it);
    }
}


void ironclad::draw_card(){

    if (draw_count >= max_draw_card) return;

    if (draw_pile.empty() && discard_pile.empty()) return;

    if (draw_pile.size() == 0) apply_discard_pile();

    auto card = draw_pile[0];
    draw_pile_remove(card);
    hand_pile_add(card);
    playCardInfo c_info;
    c_info.card = card;
    c_info.owner = this;

    emit event->card_moved(c_info, PileType::draw, PileType::hand);

    if (draw_pile.size() == 0) apply_discard_pile();

    draw_count++;
}


void ironclad::apply_discard_pile(){
    shuffle_pile(discard_pile);
    draw_pile.insert(draw_pile.end(), discard_pile.begin(), discard_pile.end());
    discard_pile.clear();
}


void ironclad::shuffle_pile(std::vector<abstractCard*>& pile){
    //QT + media
    //QT + media
    RNG::instance().shuffle(pile);
    emit event->draw_pile_shuffled();
}


void ironclad::play_card(playCardInfo& info) {
    if (info.card->get_turn_playable() == false) return;
    if (energy < info.card->get_energy()) return;

    energy -= info.card->get_energy();

    hand_pile_remove(info.card);

    if (info.card->get_exhaust()) {
        playCardInfo c_info;
        c_info.card = info.card;
        c_info.owner = this;
        emit event->card_moved(c_info, PileType::hand, PileType::none);
        exhaust_pile_add(info.card);
        emit event->card_moved(c_info, PileType::none, PileType::exhaust);
    }
    else if (info.card->get_card_type() == CardType::power){
        playCardInfo c_info;
        c_info.card = info.card;
        c_info.owner = this;
        emit event->card_moved(c_info, PileType::hand, PileType::none);
    }
    else {
        playCardInfo c_info;
        c_info.card = info.card;
        c_info.owner = this;
        emit event->card_moved(c_info, PileType::hand, PileType::none);
        discard_pile_add(info.card);
        emit event->card_moved(c_info, PileType::none, PileType::discard);
    }

    game_action actions(event);
    info.owner = this;
    actions.play_card(info);

    playInfo pl(actions);
    pl.attacker = info.owner;
    pl.target_list = info.target_list;

    for (auto item : hand_pile){
        item->update(pl);
    }
}


void ironclad::consume_all_energy() {
    set_energy(0);
}


void ironclad::at_turn_start(game_action& info) {
    energy += base_energy;
    abstractEntity::at_turn_start(info);


    playInfo pl(info);
    pl.attacker = this;

    for (int i = 0; i < hand_card_number; i++) draw_card();

    for (auto item : hand_pile){
        item->update(pl);
        item->hand_turn_start(pl);
    }

    draw_count = 0;
}


void ironclad::at_turn_end(game_action& info) {
    abstractEntity::at_turn_end(info);

    if (reset_energy) energy = 0;

    playInfo ply(info);
    ply.attacker = this;
    for (auto item : hand_pile){
        item->hand_turn_end(ply);
    }

    for (auto item : combat_deck){
        item->turn_reset();
    }

    for (int i = hand_pile.size() - 1; i >= 0; i--){


        if (hand_pile[i]->get_ethereal()){
            hand_pile_remove(hand_pile[i]);
            exhaust_pile_add(hand_pile[i]);
            playCardInfo c_info;
            c_info.card = hand_pile[i];
            c_info.owner = this;
            emit event->card_moved(c_info, PileType::hand, PileType::exhaust);
        }

        else if (hand_pile[i]->get_retain())  {}

        else {
            hand_pile_remove(hand_pile[i]);
            discard_pile_add(hand_pile[i]);
            playCardInfo c_info;
            c_info.card = hand_pile[i];
            c_info.owner = this;
            emit event->card_moved(c_info, PileType::hand, PileType::discard);
        }

    }

}


void ironclad::at_combat_start(game_action& info){
    energy = 0;

    abstractEntity::at_combat_start(info);

    combat_deck = deck;
    RNG::instance().shuffle(combat_deck);

    for (auto item : combat_deck){
        if (item->get_initial()) {
            playCardInfo c_info;
            c_info.card = item;
            c_info.owner = this;
            hand_pile_add(item);
            emit event->card_moved(c_info, PileType::draw, PileType::hand);
        }
        else {
            draw_pile_add(item);
        }
    }
}


void ironclad::at_combat_end(game_action& info) {
    abstractEntity::at_combat_end(info);

    for (auto card: deck){
        card->combat_reset();
    }

    hand_pile.clear();
    exhaust_pile.clear();
    draw_pile.clear();
    discard_pile.clear();
    combat_deck_remove_unique();
    combat_deck.clear();
}


void ironclad::damage_applied(game_action& info) {
    abstractEntity::damage_applied(info);

    for (auto item : combat_deck){
        item->damage_applied();
    }
}

void ironclad::potion_list_add(abstractPotion* pot){
    if (potion_list.size() < max_potion_number) {
        potion_list.push_back(pot);
        // emit event->potion_added(pot);
    }
}
void ironclad::potion_list_remove(abstractPotion* pot){
    for (int i = 0; i< potion_list.size(); i++){
        if (pot == potion_list[i]){
            potion_list.erase(potion_list.begin() + i);
            emit event->potion_removed(pot);
            delete pot;
            return;
        }
    }
}


void ironclad::draw_potion(drinkPotionInfo& pot) {
    if (abstractPotion::lock) return;
    if (pot.potion->playable() == false) return;

    game_action actions(event);
    pot.owner = this;
    actions.drink_potion(pot);
    potion_list_remove(pot.potion);
}