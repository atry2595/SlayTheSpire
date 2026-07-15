#include "Merchant.h"
#include "cards/cardfactory.h"
#include "items/potions/potionfactory.h"
#include"utils/RNG.h"
#include <algorithm>

Merchant::Merchant(ironclad* player): m_player(player), m_removalPrice(75)
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

int Merchant::getRemovalPrice() const
{
    return m_removalPrice;
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

    Q_ASSERT(!candidates.empty());
    if (candidates.empty()) {
        return cardID::strike;
    }

    return RNG::instance().choice(candidates);
}

cardID Merchant::getRandomCardID()
{
    static std::vector<cardID> all;
    if (all.empty()) {
        for (const auto& cid : rare_cards) {
            all.push_back(cid);
        }
        for (const auto& cid : non_rare_cards) {
            all.push_back(cid);
        }
    }

    Q_ASSERT(!all.empty());
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
        price = rng.randint(45, 75);
    }
    return isSale ? (price / 2) : price;
}

void Merchant::generateCards()
{
    RNG& rng = RNG::instance();

    CardType types[] =
        {
            CardType::attack,
            CardType::skill,
            CardType::power
        };

    // 2 Rare Cards

    for (int i = 0; i < 2; ++i)
    {

        CardType type = types[rng.randint(0,2)];

        cardID cid = getRandomCardIDByFilter(type, true);

        abstractCard* card = CardFactory::createCard(cid);

        if (!card)
            continue;

        int price = calculateCardPrice(true, false);

        m_items.emplace_back(card, price);
    }

    // 5 Non-Rare Cards

    size_t commonStart = m_items.size();

    for (int i = 0; i < 5; ++i)
    {

        CardType type = types[rng.randint(0,2)];

        cardID cid = getRandomCardIDByFilter(type, false);

        abstractCard* card = CardFactory::createCard(cid);

        if (!card)
            continue;

        int price = calculateCardPrice(false, false);

        m_items.emplace_back(card, price);
    }


    if (m_items.size() > commonStart)
    {
        int saleIndex =
            rng.randint(
                static_cast<int>(commonStart),
                static_cast<int>(m_items.size() - 1));

        m_items[saleIndex].setSale(true);

        m_items[saleIndex].setPrice(m_items[saleIndex].getPrice() / 2);
    }


    generateRandomCard();
}

void Merchant::generateRandomCard()
{
    cardID cid = getRandomCardID();

    abstractCard* card = CardFactory::createCard(cid);

    if (!card)
        return;

    int price = calculateCardPrice(card->is_rare(), false);

    m_items.emplace_back(card, price);
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
    all_potions.reserve(common_potions.size() + uncommon_potions.size() + rare_potions.size());

    all_potions.insert(all_potions.end(), common_potions.begin(), common_potions.end());
    all_potions.insert(all_potions.end(), uncommon_potions.begin(), uncommon_potions.end());
    all_potions.insert(all_potions.end(), rare_potions.begin(), rare_potions.end());

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

        abstractPotion* potion =PotionFactory::createPotion(pid, m_player);

        if (!potion)
            continue;

        m_items.emplace_back(potion, price);

    }
}

void Merchant::generateCardRemovalService()
{
    int currentRemovalPrice = getRemovalPrice();
    m_items.emplace_back(currentRemovalPrice);
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

    if(item.getType()==ShopItemType::Potion)
    {
        if(m_player->get_potion_list().size() >= 3)
            return PurchaseResult::InventoryFull;
    }
    if (!item.canBuy(m_player->get_gold())) {
        return PurchaseResult::NotEnoughGold;
    }


    if (item.getType() == ShopItemType::Card) {
        abstractCard* card = item.getCard();

        if (!card)
            return PurchaseResult::CreationError;

        m_player->deck_add(card);

        item.releaseCard();

    }
    else if (item.getType() == ShopItemType::Potion) {
            return PurchaseResult::InventoryFull;

        abstractPotion* potion = item.getPotion();

        if (!potion)
            return PurchaseResult::CreationError;

        m_player->potion_list_add(potion);

        item.releasePotion();

    }
    else if (item.getType() == ShopItemType::CardRemoval) {
        m_removalPrice += 25;
    } // حذف کارت اضافه شود

    m_player->lose_gold(item.getPrice());
    item.setPurchased(true);

    return PurchaseResult::Success;
}