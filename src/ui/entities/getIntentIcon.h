#ifndef GETINTENTICON_H
#define GETINTENTICON_H

#include "items/enemyIntent.h"
#include <QPixmap>
#include <QString>

inline int getAttackLevel(int damage)
{
    if (damage <= 4)  return 1;
    if (damage <= 9)  return 2;
    if (damage <= 14) return 3;
    if (damage <= 19) return 4;
    if (damage <= 24) return 5;
    if (damage <= 29) return 6;
    return 7;
}

inline QPixmap getIntentIcon(const enemy_intent& intent)
{
    int dmg = intent.damage * intent.repeat;
    int lvl = getAttackLevel(dmg);

    switch (intent.type)
    {
    case intent_type::attack:
        return QPixmap(QString(":/icon/intent/attack%1.ico").arg(lvl));

    case intent_type::attack_block:
        return QPixmap(QString(":/icon/intent/attack%1_block.ico").arg(lvl));

    case intent_type::attack_buff:
        return QPixmap(QString(":/icon/intent/attack%1_buff.ico").arg(lvl));

    case intent_type::attack_debuff:
        return QPixmap(QString(":/icon/intent/attack%1_debuff.ico").arg(lvl));

    case intent_type::buff:
        return QPixmap(":/icon/intent/buff.ico");

    case intent_type::debuff:
        return QPixmap(":/icon/intent/debuff.ico");

    case intent_type::block:
        return QPixmap(":/icon/intent/block.ico");

    case intent_type::block_buff:
        return QPixmap(":/icon/intent/block-buff.ico");

    case intent_type::escape:
        return QPixmap(":/icon/intent/escape.ico");

    case intent_type::special:
        return QPixmap(":/icon/intent/unknown.ico");

    default:
        return QPixmap();
    }
}

#endif // GETINTENTICON_H