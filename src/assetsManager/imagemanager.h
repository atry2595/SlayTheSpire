#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <QHash>
#include <QPixmap>
#include "core/setting.h"
#include "categories/cards.h"
#include "categories/enemies.h"
#include "categories/intents.h"
#include "categories/potions.h"
#include "categories/powers.h"
#include "categories/relics.h"
#include "items/enemyIntent.h"

class imageManager
{
    imageManager();

    QHash<QString, QPixmap> icon_table;
    QHash<powerID, QPixmap> power_table;
    QHash<QString, QPixmap> intent_table;
    QHash<potionID, QPixmap> potion_table;
    QHash<relicID, QPixmap> relic_table;

    QHash<QString, QPixmap> frame_table;
    QHash<cardTemplates, QPixmap> back_table;
    QHash<cardID, QPixmap> card_table;

    QHash<entityID, QPixmap> entity_table;
    QHash<entityID, QPixmap> entity1x1_table;
    QHash<skins, QPixmap> ironclad_table;

    QHash<QString, QPixmap> effect_table;

    QHash<QString, QPixmap> background_table;

public:
    static imageManager& instance();

    QPixmap& getIcon(QString name);
    QPixmap& getPowerIcon(powerID id);
    QPixmap& getIntentIcon(const enemy_intent& intent);
    QPixmap& getPotionIcon(potionID id);
    QPixmap& getRelicIcon(relicID id);

    QPixmap& getCardFrame(cardTemplates tmpel, CardType id);
    QPixmap& getCardBack(cardTemplates tmpel);
    QPixmap& getCardImage(cardID id);

    QPixmap& getEntityImage(entityID);
    QPixmap& getEntity1x1(entityID);
    QPixmap& getIroncladImage(skins skin);

    QPixmap& getEffectImage(QString name);

    QPixmap& getBackroundImage();
};

#endif // IMAGEMANAGER_H
