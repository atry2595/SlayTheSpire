#include "ShopItem.h"

ShopItem::ShopItem(ShopItemType type, int id, int price, const QString& name)
    : m_type(type), m_id(id), m_price(price), m_name(name), m_isSale(false), m_isPurchased(false)
{
}

ShopItemType ShopItem::getType() const
{
    return m_type;
}

int ShopItem::getId() const
{
    return m_id;
}

int ShopItem::getPrice() const
{
    return m_price;
}

void ShopItem::setPrice(int price)
{
    m_price = price;
}

QString ShopItem::getName() const
{
    return m_name;
}

bool ShopItem::isSale() const
{
    return m_isSale;
}

void ShopItem::setSale(bool sale)
{
    m_isSale = sale;
}

bool ShopItem::isPurchased() const
{
    return m_isPurchased;
}

void ShopItem::setPurchased(bool purchased)
{
    m_isPurchased = purchased;
}
