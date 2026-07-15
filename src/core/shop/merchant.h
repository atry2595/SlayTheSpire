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

    void generateCards();
    void generateRandomCard();
    void generateSpecialCard(); //؟
    int calculateCardPrice(bool isRare, bool isSale);
    cardID getRandomCardIDByFilter(CardType type, bool isRare);
    cardID getRandomCardID();

    void generatePotions();
    void generateCardRemovalService();
    int calculatePotionPrice(PotionType rarity);
    static QString getCardNameByID(cardID cid);

public:
    explicit Merchant(ironclad* player);

    const std::vector<ShopItem>& getItems() const ;
    int getRemovalPrice() const ;
    void generateShop();
    PurchaseResult buyItem(size_t index);
};

#endif