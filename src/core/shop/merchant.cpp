#include "Merchant.h"
#include "cards/cardfactory.h"
#include "items/potions/potionfactory.h"
#include"utils/RNG.h"
#include <algorithm>

Merchant::Merchant(ironclad* player)
    : m_player(player), m_removalBasePrice(75), m_removalCount(0)
{
}

void Merchant::generateShop()
{
    m_items.clear();
    generateCards();
    generatePotions();
    generateCardRemovalService();
}

cardID Merchant::getRandomCardIDByFilter(CardType type, CardRarity rarity)
{
    std::vector<cardID> candidates;
    if (rarity == CardRarity::rare) {
        for (const auto& cid : rare_cards) {
            abstractCard* temp = CardFactory::createCard(cid);
            if (temp) {
                if (temp->get_card_type() == type) candidates.push_back(cid);
                delete temp;
            }
        }
    }
    else {
        for (const auto& cid : non_rare_cards) {
            abstractCard* temp = CardFactory::createCard(cid);
            if (temp) {
                if (temp->get_card_type() == type) candidates.push_back(cid);
                delete temp;
            }
        }
    }

    if (candidates.empty()) {
        return cardID::strike;
    }
    return RNG::instance().choice(candidates);
}

cardID Merchant::getRandomCardID()
{
    std::vector<cardID> all;
    for (const auto& cid : rare_cards) all.push_back(cid);
    for (const auto& cid : non_rare_cards) all.push_back(cid);

    if (all.empty()) {
        return cardID::strike;
    }
    return RNG::instance().choice(all);
}

int Merchant::calculateCardPrice(CardRarity rarity, bool isSale)
{
    int price = 0;
    RNG& rng = RNG::instance();
    switch (rarity) {
    case CardRarity::common:   price = rng.randint(45, 55); break;
    case CardRarity::uncommon: price = rng.randint(68, 82); break;
    case CardRarity::rare:     price = rng.randint(135, 165); break;
    default:                   price = 50; break;
    }
    return isSale ? (price / 2) : price;
}

void Merchant::generateCards()
{
    RNG& rng = RNG::instance();

    // Rare 2
    for (int i = 0; i < 2; ++i) {
        CardType type = static_cast<CardType>(rng.randint(0, 2));
        cardID cid = getRandomCardIDByFilter(type, CardRarity::rare);
        int price = calculateCardPrice(CardRarity::rare, false);
        abstractCard* temp = CardFactory::createCard(cid);
        std::string name = temp ? temp->get_name() : "Rare Card";
        delete temp;
        m_items.emplace_back(ShopItemType::Card, static_cast<int>(cid), price, name);
    }

    size_t commonStartIndex = m_items.size();

    //Common 5
    for (int i = 0; i < 5; ++i) {
        CardType type = static_cast<CardType>(rng.randint(0, 2));
        cardID cid = getRandomCardIDByFilter(type, CardRarity::common);
        int price = calculateCardPrice(CardRarity::common, false);
        abstractCard* temp = CardFactory::createCard(cid);
        std::string name = temp ? temp->get_name() : "Common Card";
        delete temp;
        m_items.emplace_back(ShopItemType::Card, static_cast<int>(cid), price, name);
    }

    if (m_items.size() > commonStartIndex) {
        int saleIndex = rng.randint(static_cast<int>(commonStartIndex), static_cast<int>(m_items.size() - 1));
        m_items[saleIndex].setSale(true);
        m_items[saleIndex].setPrice(m_items[saleIndex].getPrice() / 2);
    }

    generateSpecialCard();
}

void Merchant::generateSpecialCard()
{
    cardID cid = getRandomCardID();
    int price = calculateCardPrice(CardRarity::uncommon, false);
    abstractCard* temp = CardFactory::createCard(cid);
    std::string name = temp ? temp->get_name() + " (Special)" : "Special Card";
    delete temp;
    m_items.emplace_back(ShopItemType::Card, static_cast<int>(cid), price, name);
}


int Merchant::calculatePotionPrice(PotionType rarity)
{
    RNG& rng = RNG::instance();
    switch (rarity) {
    case PotionType::common:return rng.randint(48, 52);
    case PotionType::uncommon:return rng.randint(72, 78);
    case PotionType::rare:return rng.randint(95, 105);
    default:return 50;
    }
}

void Merchant::generatePotions()
{
    std::vector<potionID> all_potions;
    for (const auto& pid : common_potions) all_potions.push_back(pid);
    for (const auto& pid : uncommon_potions) all_potions.push_back(pid);
    for (const auto& pid : rare_potions) all_potions.push_back(pid);

    if (all_potions.empty()) return;

    RNG& rng = RNG::instance();

    for (int i = 0; i < 3; ++i) {
        potionID pid = rng.choice(all_potions);
        PotionType rarity = PotionType::common;

        if (std::find(uncommon_potions.begin(), uncommon_potions.end(), pid) != uncommon_potions.end()) {
            rarity = PotionType::uncommon;
        }
        else if (std::find(rare_potions.begin(), rare_potions.end(), pid) != rare_potions.end()) {
            rarity = PotionType::rare;
        }

        int price = calculatePotionPrice(rarity);
        abstractPotion* temp = PotionFactory::createPotion(pid, m_player);
        std::string name = temp ? temp->get_name() : "Potion";
        delete temp;

        m_items.emplace_back(ShopItemType::Potion, static_cast<int>(pid), price, name);
    }
}

void Merchant::generateCardRemovalService()
{
    int currentRemovalPrice = getRemovalPrice();
    m_items.emplace_back(ShopItemType::CardRemoval, -1, currentRemovalPrice, "Card Removal Service");
}