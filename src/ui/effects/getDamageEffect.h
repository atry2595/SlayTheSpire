#ifndef GETDAMAGEEFFECT_H
#define GETDAMAGEEFFECT_H

#include <QPixmap>
#include <QSizeF>
#include "categories/cards.h"
#include "categories/enemies.h"

struct damageEffectInfo {
    QPixmap image;
    QSizeF size;
};

inline damageEffectInfo getDamageEffect(cardID id) {

    switch (id) {
        case cardID::reaper: return {QPixmap(":/image/effect/dmg.png"), QSizeF(500, 181)};
        case cardID::bludgeon: return {QPixmap(":/image/effect/web_dmg.png"), QSizeF(500, 372)};
        case cardID::feed: return {QPixmap(":/image/effect/squeeze.png"), QSizeF(500, 534)};
        case cardID::immolate: return {QPixmap(":/image/effect/fire.png"), QSizeF(500, 447)};
        case cardID::whirlwind: return {QPixmap(":/image/effect/dmg.png"), QSizeF(500, 181)};
        case cardID::blood_for_blood: return {QPixmap(":/image/effect/rotary.png"), QSizeF(500, 349)};
        case cardID::bash: return {QPixmap(":/image/effect/mace.png"), QSizeF(500, 371)};
        case cardID::twin_strike: return {QPixmap(":/image/effect/twin.png"), QSizeF(500, 367)};
        case cardID::perfected_strike: return {QPixmap(":/image/effect/dmg2.png"), QSizeF(500, 223)};
        case cardID::clash: return {QPixmap(":/image/effect/feather.png"), QSizeF(500, 479)};
        case cardID::uppercut: return {QPixmap(":/image/effect/rotary_blow.png"), QSizeF(500, 336)};
        case cardID::heavy_blade: return {QPixmap(":/image/effect/sickle.png"), QSizeF(500, 402)};
        case cardID::pommel_strike: return {QPixmap(":/image/effect/dmg3.png"), QSizeF(500, 452)};
        case cardID::carnage: return {QPixmap(":/image/effect/spearhead.png"), QSizeF(500, 488)};
        case cardID::hemokinesis: return {QPixmap(":/image/effect/wings.png"), QSizeF(500, 194)};

        case cardID::strike:
        default:
            return {QPixmap(":/image/effect/dmg.png"), QSizeF(500, 181)};

    }
}

inline damageEffectInfo getDamageEffect(entityID id) {
    switch(id) {
        case entityID::cultist: return {QPixmap(":/image/effect/feather.png"), QSizeF(500, 479)};
        case entityID::jaw_worm: return {QPixmap(":/image/effect/bite.png"), QSizeF(500, 427)};
        case entityID::red_louse: return {QPixmap(":/image/effect/dmg.png"), QSizeF(500, 181)};
        case entityID::green_louse: return {QPixmap(":/image/effect/dmg.png"), QSizeF(500, 181)};
        case entityID::small_slime: return {QPixmap(":/image/effect/dmg.png"), QSizeF(500, 181)};
        case entityID::medium_slime: return {QPixmap(":/image/effect/dmg2.png"), QSizeF(500, 223)};
        case entityID::large_slime: return {QPixmap(":/image/effect/dmg2.png"), QSizeF(500, 223)};
        case entityID::looter: return {QPixmap(":/image/effect/wings.png"), QSizeF(500, 194)};
        case entityID::mugger: return {QPixmap(":/image/effect/wings.png"), QSizeF(500, 194)};
        case entityID::blue_slaver: return {QPixmap(":/image/effect/spearhead.png"), QSizeF(500, 488)};
        case entityID::red_slaver: return {QPixmap(":/image/effect/web.png"), QSizeF(500, 393)};
        case entityID::spheric_guardian: return {QPixmap(":/image/effect/dmg3.png"), QSizeF(500, 452)};
        case entityID::gremlin_nob: return {QPixmap(":/image/effect/mace.png"), QSizeF(500, 371)};
        case entityID::sentry: return {QPixmap(":/image/effect/dmg.png"), QSizeF(500, 181)};
        case entityID::book_of_stabbing: return {QPixmap(":/image/effect/sickle.png"), QSizeF(500, 402)};
        case entityID::taskmaster: return {QPixmap(":/image/effect/twin.png"), QSizeF(500, 376)};
        case entityID::slime_boss: return {QPixmap(":/image/effect/explosion.png"), QSizeF(500, 398)};
        case entityID::hexaghost: return {QPixmap(":/image/effect/rotary.png"), QSizeF(500, 349)};
        case entityID::the_champ: return {QPixmap(":/image/effect/rotary_blow.png"), QSizeF(500, 336)};
        default:
            return {QPixmap(":/image/effect/dmg.png"), QSizeF(500, 181)};
    }
}

#endif // GETDAMAGEEFFECT_H
