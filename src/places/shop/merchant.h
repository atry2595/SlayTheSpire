#ifndef MERCHANT_H
#define MERCHANT_H

#include <QObject>
#include <QString>
#include <vector>
#include "shopitem.h"
#include "entity/ironclad.h"
#include "categories/cards.h"
#include "categories/potions.h"

enum class PurchaseResult {
    Success,
    InvalidIndex,
    AlreadyPurchased,
    NotEnoughGold,
    InventoryFull,
    InvalidPlayer,
    CreationError
};

class Merchant
{
private:
    ironclad* m_player;
    std::vector<ShopItem> m_items;
    int m_removalPrice;
    static constexpr int MYSTERY_PRICE = 100;

    void generateCards();
    void generateRandomCard();
    void generatePotions();
    void generateCardRemovalService();
    abstractCard* generateRandomMysteryCard();

    int calculateCardPrice(bool isRare);

    int calculatePotionPrice(PotionType rarity);

public:
    explicit Merchant(ironclad* player);

    const std::vector<ShopItem>& getItems() const ;
    int getRemovalPrice() const ;
    void generateShop();
    PurchaseResult buyItem(size_t index);
};

#endif