#ifndef SHOPITEM_H
#define SHOPITEM_H

#include <QString>
#include "cards/abstractcard.h"
#include "items/potions/abstractpotion.h"

enum class ShopItemType {
    Card,
    Potion,
    CardRemoval
};

class ShopItem
{
private:
    ShopItemType m_type;
    abstractCard* m_card;
    abstractPotion* m_potion;
    int m_price;
    bool m_isSale;
    bool m_isPurchased;

public:

    ShopItem(abstractCard* card, int price);
    ShopItem(abstractPotion* potion, int price);
    ShopItem(int removalPrice);

    ~ShopItem();

    ShopItemType getType() const;

    abstractCard* getCard() const;
    abstractPotion* getPotion() const;

    void releaseCard();
    void releasePotion();

    int getPrice() const;
    void setPrice(int price);

    bool isSale() const;
    void setSale(bool sale);

    bool isPurchased() const;
    void setPurchased(bool purchased);

    bool canBuy(int gold) const;
};

#endif // SHOPITEM_H
