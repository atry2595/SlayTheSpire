#ifndef GETPOTIONICON_H
#define GETPOTIONICON_H

#include "categories/potions.h"
#include <QPixmap>

inline QPixmap getPotionIcon(potionID id) {
    switch (id){
    case potionID::block_potion:
        return QPixmap(":/icon/potion/block_potion.ico");

    case potionID::white_blood_potion:
        return QPixmap(":/icon/potion/blood_potion.ico");

    case potionID::cultist_potion:
        return QPixmap(":/icon/potion/cultist_potion.ico");

    case potionID::dexterity_potion:
        return QPixmap(":/icon/potion/dexterity_potion.ico");

    case potionID::energy_potion:
        return QPixmap(":/icon/potion/energy_potion.ico");

    case potionID::explosive_potion:
        return QPixmap(":/icon/potion/explosive_potion.ico");

    case potionID::fairy_in_a_bottle:
        return QPixmap(":/icon/potion/fairy_in_a_bottle.ico");

    case potionID::fear_potion:
        return QPixmap(":/icon/potion/fear_potion.ico");

    case potionID::fire_potion:
        return QPixmap(":/icon/potion/fire_potion.ico");

    case potionID::strength_potion:
        return QPixmap(":/icon/potion/strength_potion.ico");

    case potionID::swift_potion:
        return QPixmap(":/icon/potion/swift_potion.ico");

    case potionID::weak_potion:
        return QPixmap(":/icon/potion/weak_potion.ico");



    default:
        return QPixmap();
    }
}


#endif // GETPOTIONICON_H
