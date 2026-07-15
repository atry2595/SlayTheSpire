#include "Merchant.h"
#include "cards/cardfactory.h"
#include "items/potions/potionfactory.h"
#include"utils/RNG.h"
#include <algorithm>

Merchant::Merchant(ironclad* player)
    : m_player(player), m_removalPrice(75)
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

QString Merchant::getCardNameByID(cardID cid)
{
    switch (cid) {
    case cardID::strike: return "Strike";
    case cardID::defend: return "Defend";
    case cardID::bash: return "Bash";
    case cardID::clash: return "Clash";
    case cardID::heavy_blade: return "Heavy Blade";
    case cardID::perfected_strike: return "Perfected Strike";
    case cardID::shrug_it_off: return "Shrug It Off";
    case cardID::twin_strike: return "Twin Strike";
    case cardID::blood_for_blood: return "Blood for Blood";
    case cardID::carnage: return "Carnage";
    case cardID::hemokinesis: return "Hemokinesis";
    case cardID::uppercut: return "Uppercut";
    case cardID::bludgeon: return "Bludgeon";
    case cardID::feed: return "Feed";
    case cardID::immolate: return "Immolate";
    default: return "Unknown Card";
    }
}

cardID Merchant::getRandomCardIDByFilter(CardType type, bool isRare)
{
    std::vector<cardID> candidates;
    const auto& listSource = isRare ? rare_cards : non_rare_cards;

    for (const auto& cid : listSource) {
        abstractCard* temp = CardFactory::createCard(cid);
        if (temp) {
            if (temp->get_card_type() == type && temp->is_rare() == isRare) {
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
        QString name = getCardNameByID(cid);
        m_items.emplace_back(ShopItemType::Card, static_cast<int>(cid), price, name);
    }

    size_t commonStartIndex = m_items.size();

    //Non-Rare 5
    for (int i = 0; i < 5; ++i) {
        CardType type = static_cast<CardType>(rng.randint(0, 2));
        cardID cid = getRandomCardIDByFilter(type, false);
        int price = calculateCardPrice(false, false);
        QString name = getCardNameByID(cid);
        m_items.emplace_back(ShopItemType::Card, static_cast<int>(cid), price, name);
    }

    if (m_items.size() > commonStartIndex) {
        int saleIndex = rng.randint(static_cast<int>(commonStartIndex), static_cast<int>(m_items.size() - 1));
        m_items[saleIndex].setSale(true);
        m_items[saleIndex].setPrice(m_items[saleIndex].getPrice() / 2);
    }

    //generateSpecialCard();
}

void Merchant::generateRandomCard()
{
    cardID cid = getRandomCardID();
    int price = calculateCardPrice(false, false);
    QString name = getCardNameByID(cid);
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
    if (!item.canBuy(m_player->get_gold())) {
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
        m_removalPrice += 25;
    }

    m_player->lose_gold(item.getPrice());
    item.setPurchased(true);

    return PurchaseResult::Success;
}