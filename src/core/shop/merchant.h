#ifndef MERCHANT_H
#define MERCHANT_H

#include <QObject>
#include <vector>
#include "shopitem.h"
#include "entity/ironclad.h"
#include "categories/cards.h"
#include "categories/potions.h"


class Merchant
{
private:
    ironclad* m_player;
    std::vector<ShopItem> m_items;
    int m_removalBasePrice;
    int m_removalCount;

    void generateCards();
    void generateSpecialCard();
    int calculateCardPrice(CardRarity rarity, bool isSale);
    cardID getRandomCardIDByFilter(CardType type, CardRarity rarity);
    cardID getRandomCardID();

    void generatePotions();
    void generateCardRemovalService();
    int calculatePotionPrice(PotionType rarity);

public:
    explicit Merchant(ironclad* player);

    const std::vector<ShopItem>& getItems() const { return m_items; }
    int getRemovalPrice() const { return m_removalBasePrice + (m_removalCount * 25); }
    void generateShopInventory();
};

#endif