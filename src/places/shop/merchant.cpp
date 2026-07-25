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
    generateRandomCard();
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

abstractCard* Merchant::generateRandomMysteryCard()
{
    RNG& rng = RNG::instance();

    int roll = rng.randint(1, 6);

    // Curse (1/6)

    if (roll == 1)
    {
        std::vector<cardID> pool = curse_cards;
        return CardFactory::createCard(rng.choice(pool));
    }

    // Rare (2/6)

    else if (roll <= 3)
    {
        std::vector<cardID> pool = rare_cards;
        return CardFactory::createCard(rng.choice(pool));

    }

    // Non Rare (3/6)

    std::vector<cardID> pool = non_rare_cards;
    return CardFactory::createCard(rng.choice(pool));
}

int Merchant::calculateCardPrice(bool isRare)
{
    int price = 0;
    RNG& rng = RNG::instance();
    if (isRare) {
        price = rng.randint(135, 165);
    } else {
        price = rng.randint(45, 75);
    }
    return price;
}

void Merchant::generateCards()
{
    RNG& rng = RNG::instance();

    std::vector<cardID> rarePool = rare_cards;
    std::vector<cardID> nonRarePool = non_rare_cards;

    // 2 Rare Cards
    for (int i = 0; i < 2 && !rarePool.empty(); ++i)
    {
        int index = rng.randint(0, static_cast<int>(rarePool.size() - 1));

        cardID cid = rarePool[index];
        rarePool.erase(rarePool.begin() + index);

        abstractCard* card = CardFactory::createCard(cid);

        if (!card)
            continue;

        int price = calculateCardPrice(card->is_rare());

        m_items.emplace_back(card, price);
    }

    // 5 Non Rare Cards
    size_t commonStart = m_items.size();

    for (int i = 0; i < 5 && !nonRarePool.empty(); ++i)
    {
        int index = rng.randint(0, static_cast<int>(nonRarePool.size() - 1));

        cardID cid = nonRarePool[index];
        nonRarePool.erase(nonRarePool.begin() + index);

        abstractCard* card = CardFactory::createCard(cid);

        if (!card)
            continue;

        int price = calculateCardPrice(card->is_rare());

        m_items.emplace_back(card, price);
    }

    if (m_items.size() > commonStart)
    {
        int saleIndex = rng.randint(
            static_cast<int>(commonStart),
            static_cast<int>(m_items.size() - 1));

        m_items[saleIndex].setSale(true);
        m_items[saleIndex].setPrice(m_items[saleIndex].getPrice() / 2);
    }
}

void Merchant::generateRandomCard()
{
    abstractCard* card = nullptr;

    while (true)
    {
        card = generateRandomMysteryCard();

        if (!card)
            return;

        bool duplicate = false;

        for (const auto& item : m_items)
        {
            if (item.getType() != ShopItemType::Card)
                continue;

            abstractCard* shopCard = item.getCard();

            if (shopCard && shopCard->get_card_id() == card->get_card_id())
            {
                duplicate = true;
                break;
            }
        }

        if (!duplicate)
            break;

        delete card;
    }

    m_items.emplace_back(card, MYSTERY_PRICE);
    m_items.back().setMystery(true);
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

    for (int i = 0; i < 3  && !all_potions.empty(); ++i) {
        potionID pid = rng.choice(all_potions);
        all_potions.erase(
            std::remove(all_potions.begin(), all_potions.end(), pid),
            all_potions.end()
            );

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
    m_items.emplace_back(m_removalPrice);
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

    else if(item.getType()==ShopItemType::Potion)
    {
        abstractPotion* potion=item.getPotion();

        if(!potion)
            return PurchaseResult::CreationError;

        m_player->potion_list_add(potion);

        item.releasePotion();
    }

    else if (item.getType() == ShopItemType::CardRemoval)
    {
        std::vector<abstractCard*> selectable;

        for (auto card : m_player->get_deck())
        {
            if (card->can_remove_from_deck())
                selectable.push_back(card);
        }

        if (selectable.empty())
            return PurchaseResult::CreationError;

        abstractCard* selected = ironclad::select_card(selectable);

        if (!selected)
            return PurchaseResult::CreationError;

        m_player->deck_remove(selected);

        m_removalPrice += 25;
    }

    m_player->lose_gold(item.getPrice());
    item.setPurchased(true);0

    return PurchaseResult::Success;
}