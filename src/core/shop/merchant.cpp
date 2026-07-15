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

const std::vector<ShopItem>& Merchant::getItems() const
{
    return m_items;
}

cardID Merchant::getRandomCardIDByFilter(CardType type, bool isRare)
{
    std::vector<cardID> candidates;
    const auto& listSource = isRare ? rare_cards : non_rare_cards;

    for (const auto& cid : listSource) {
        abstractCard* temp = CardFactory::createCard(cid);
        if (temp) {
            if (temp->get_card_type() == type) {
                candidates.push_back(cid);
            }
            delete temp;
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

int Merchant::calculateCardPrice(bool isRare, bool isSale)
{
    int price = 0;
    RNG& rng = RNG::instance();
    if (isRare) {
        price = rng.randint(135, 165);
    } else {
        price = rng.randint(50, 80);
    }
    return isSale ? (price / 2) : price;
}

void Merchant::generateCards()
{
    RNG& rng = RNG::instance();

    // Rare 2
    for (int i = 0; i < 2; ++i) {
        CardType type = static_cast<CardType>(rng.randint(0, 2));
        cardID cid = getRandomCardIDByFilter(type, true);
        int price = calculateCardPrice(true, false);
        abstractCard* temp = CardFactory::createCard(cid);
        QString name = temp ? temp->get_name() : "Rare Card";
        delete temp;
        m_items.emplace_back(ShopItemType::Card, static_cast<int>(cid), price, name);
    }

    size_t commonStartIndex = m_items.size();

    //Non-Rare 5
    for (int i = 0; i < 5; ++i) {
        CardType type = static_cast<CardType>(rng.randint(0, 2));
        cardID cid = getRandomCardIDByFilter(type, false);
        int price = calculateCardPrice(false, false);
        abstractCard* temp = CardFactory::createCard(cid);
        QString name = temp ? temp->get_name() : "Common Card";
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
        } else if (std::find(rare_potions.begin(), rare_potions.end(), pid) != rare_potions.end()) {
            rarity = PotionType::rare;
        }

        int price = calculatePotionPrice(rarity);

        abstractPotion* temp = PotionFactory::createPotion(pid, m_player);
        QString name = temp ? temp->get_name() : "Potion";
        delete temp;

        m_items.emplace_back(ShopItemType::Potion, static_cast<int>(pid), price, name);
    }
}

void Merchant::generateCardRemovalService()
{
    int currentRemovalPrice = getRemovalPrice();
    m_items.emplace_back(ShopItemType::CardRemoval, -1, currentRemovalPrice, "Card Removal Service");
}

int Merchant::getRemovalPrice() const
{
    return m_removalBasePrice + (m_removalCount * 25);
}

PurchaseResult Merchant::buyItem(size_t index)
{
    if (index >= m_items.size()) {
        return PurchaseResult::InvalidIndex;
    }

    ShopItem& item = m_items[index];

    if (item.isPurchased()) {
        return PurchaseResult::AlreadyPurchased;
    }

    if (!m_player) {
        return PurchaseResult::InvalidPlayer;
    }

    if (m_player->get_gold() < item.getPrice()) {
        return PurchaseResult::NotEnoughGold;
    }

    if (item.getType() == ShopItemType::Card) {
        cardID cid = static_cast<cardID>(item.getId());
        abstractCard* newCard = CardFactory::createCard(cid);
        if (!newCard) {
            return PurchaseResult::CreationError;
        }
        m_player->deck_add(newCard);
    }
    else if (item.getType() == ShopItemType::Potion) {
        if (m_player->get_potion_list().size() >= 3) {
            return PurchaseResult::InventoryFull;
        }

        potionID pid = static_cast<potionID>(item.getId());
        abstractPotion* newPotion = PotionFactory::createPotion(pid, m_player);
        if (!newPotion) {
            return PurchaseResult::CreationError;
        }

        m_player->potion_list_add(newPotion);
    }
    else if (item.getType() == ShopItemType::CardRemoval) {
        m_removalCount++;
    }

    m_player->lose_gold(item.getPrice());
    item.setPurchased(true);

    return PurchaseResult::Success;
}