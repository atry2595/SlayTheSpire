#ifndef GETDAMAGEEFFECT_H
#define GETDAMAGEEFFECT_H

#include <QPixmap>
#include <QSizeF>
#include "categories/cards.h"
#include "categories/enemies.h"
#include "assetsManager/imagemanager.h"

struct damageEffectInfo {
    QPixmap& image;
    QSizeF size;
};

inline damageEffectInfo getDamageEffect(cardID id) {
    auto mng = imageManager::instance();

    switch (id) {
        case cardID::reaper: return {mng.getEffectImage("dmg"), QSizeF(500, 181)};
        case cardID::bludgeon: return {mng.getEffectImage("web_dmg"), QSizeF(500, 372)};
        case cardID::feed: return {mng.getEffectImage("squeeze"), QSizeF(500, 534)};
        case cardID::immolate: return {mng.getEffectImage("fire"), QSizeF(500, 447)};
        case cardID::whirlwind: return {mng.getEffectImage("dmg"), QSizeF(500, 181)};
        case cardID::blood_for_blood: return {mng.getEffectImage("rotary"), QSizeF(500, 349)};
        case cardID::bash: return {mng.getEffectImage("mace"), QSizeF(500, 371)};
        case cardID::twin_strike: return {mng.getEffectImage("twin"), QSizeF(500, 367)};
        case cardID::perfected_strike: return {mng.getEffectImage("dmg2"), QSizeF(500, 223)};
        case cardID::clash: return {mng.getEffectImage("feather"), QSizeF(500, 479)};
        case cardID::uppercut: return {mng.getEffectImage("rotary_blow"), QSizeF(500, 336)};
        case cardID::heavy_blade: return {mng.getEffectImage("sickle"), QSizeF(500, 402)};
        case cardID::pommel_strike: return {mng.getEffectImage("dmg3"), QSizeF(500, 452)};
        case cardID::carnage: return {mng.getEffectImage("spearhead"), QSizeF(500, 488)};
        case cardID::hemokinesis: return {mng.getEffectImage("wings"), QSizeF(500, 194)};

        case cardID::strike:
        default:
            return {mng.getEffectImage("dmg"), QSizeF(500, 181)};

    }
}

inline damageEffectInfo getDamageEffect(entityID id) {
    auto mng = imageManager::instance();
    switch(id) {
        case entityID::cultist: return {mng.getEffectImage("feather"), QSizeF(500, 479)};
        case entityID::jaw_worm: return {mng.getEffectImage("bite"), QSizeF(500, 427)};
        case entityID::red_louse: return {mng.getEffectImage("dmg"), QSizeF(500, 181)};
        case entityID::green_louse: return {mng.getEffectImage("dmg"), QSizeF(500, 181)};
        case entityID::small_slime: return {mng.getEffectImage("dmg"), QSizeF(500, 181)};
        case entityID::medium_slime: return {mng.getEffectImage("dmg2"), QSizeF(500, 223)};
        case entityID::large_slime: return {mng.getEffectImage("dmg2"), QSizeF(500, 223)};
        case entityID::looter: return {mng.getEffectImage("wings"), QSizeF(500, 194)};
        case entityID::mugger: return {mng.getEffectImage("wings"), QSizeF(500, 194)};
        case entityID::blue_slaver: return {mng.getEffectImage("spearhead"), QSizeF(500, 488)};
        case entityID::red_slaver: return {mng.getEffectImage("web"), QSizeF(500, 393)};
        case entityID::spheric_guardian: return {mng.getEffectImage("dmg3"), QSizeF(500, 452)};
        case entityID::gremlin_nob: return {mng.getEffectImage("mace"), QSizeF(500, 371)};
        case entityID::sentry: return {mng.getEffectImage("dmg"), QSizeF(500, 181)};
        case entityID::book_of_stabbing: return {mng.getEffectImage("sickle"), QSizeF(500, 402)};
        case entityID::taskmaster: return {mng.getEffectImage("twin"), QSizeF(500, 376)};
        case entityID::slime_boss: return {mng.getEffectImage("explosion"), QSizeF(500, 398)};
        case entityID::hexaghost: return {mng.getEffectImage("rotary"), QSizeF(500, 349)};
        case entityID::the_champ: return {mng.getEffectImage("rotary_blow"), QSizeF(500, 336)};
        default:
            return {mng.getEffectImage("dmg"), QSizeF(500, 181)};
    }
}

#endif // GETDAMAGEEFFECT_H
