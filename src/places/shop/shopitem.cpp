#include "ShopItem.h"

ShopItem::ShopItem(abstractCard* card, int price)
{
    m_type = ShopItemType::Card;

    m_card = card;
    m_potion = nullptr;

    m_price = price;

    m_isSale = false;
    m_isPurchased = false;
    m_isHidden = false;
}

ShopItem::ShopItem(abstractPotion* potion, int price)
{
    m_type = ShopItemType::Potion;

    m_card = nullptr;
    m_potion = potion;

    m_price = price;

    m_isSale = false;
    m_isPurchased = false;
    m_isHidden = false;
}

ShopItem::ShopItem(int removalPrice)
{
    m_type = ShopItemType::CardRemoval;

    m_card = nullptr;
    m_potion = nullptr;

    m_price = removalPrice;

    m_isSale = false;
    m_isPurchased = false;
    m_isHidden = false;
}

ShopItem::ShopItem(ShopItem&& other) noexcept
{
    m_type = other.m_type;
    m_card = other.m_card;
    m_potion = other.m_potion;
    m_price = other.m_price;
    m_isSale = other.m_isSale;
    m_isPurchased = other.m_isPurchased;
    m_isHidden = other.m_isHidden;

    other.m_card = nullptr;
    other.m_potion = nullptr;
}

ShopItem& ShopItem::operator=(ShopItem&& other) noexcept
{
    if (this != &other)
    {
        delete m_card;
        delete m_potion;

        m_type = other.m_type;
        m_card = other.m_card;
        m_potion = other.m_potion;
        m_price = other.m_price;
        m_isSale = other.m_isSale;
        m_isPurchased = other.m_isPurchased;
        m_isHidden = other.m_isHidden;

        other.m_card = nullptr;
        other.m_potion = nullptr;
    }

    return *this;
}

ShopItem::~ShopItem()
{
    if (!m_isPurchased)
    {
        delete m_card;
        delete m_potion;
    }
}

ShopItemType ShopItem::getType() const
{
    return m_type;
}

abstractCard* ShopItem::getCard() const
{
    return m_card;
}

abstractPotion* ShopItem::getPotion() const
{
    return m_potion;
}

void ShopItem::releaseCard()
{
    m_card = nullptr;
}

void ShopItem::releasePotion()
{
    m_potion = nullptr;
}

int ShopItem::getPrice() const
{
    return m_price;
}

void ShopItem::setPrice(int price)
{
    m_price = price;
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

bool ShopItem::canBuy(int gold) const
{
    return gold >= m_price;
}

void ShopItem::setPurchased(bool purchased)
{
    m_isPurchased = purchased;
}

bool ShopItem::isMystery() const
{
    return m_isHidden;
}

void ShopItem::setMystery(bool mystery)
{
    m_isHidden = mystery;
}
