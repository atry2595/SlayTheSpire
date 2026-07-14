#ifndef SHOPITEM_H
#define SHOPITEM_H

#include <QString>

enum class ShopItemType {
    Card,
    Potion,
    CardRemoval
};

class ShopItem
{
private:
    ShopItemType m_type;
    int m_id;
    int m_price;
    QString m_name;
    bool m_isSale;
    bool m_isPurchased;

public:
    ShopItem(ShopItemType type, int id, int price, const QString& name);

    ShopItemType getType() const;
    int getId() const;
    int getPrice() const;
    void setPrice(int price);
    QString getName() const;

    bool isSale() const;
    void setSale(bool sale);

    bool isPurchased() const;
    void setPurchased(bool purchased);
};

#endif // SHOPITEM_H
