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
    bool m_isHidden;
public:

    ShopItem(abstractCard* card, int price);
    ShopItem(abstractPotion* potion, int price);
    ShopItem(int removalPrice);

    ~ShopItem();

    ShopItem(const ShopItem&) = delete;
    ShopItem& operator=(const ShopItem&) = delete;
    ShopItem(ShopItem&& other) noexcept;
    ShopItem& operator=(ShopItem&& other) noexcept;

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

    bool isMystery() const;
    void setMystery(bool mystery);
};

#endif // SHOPITEM_H
