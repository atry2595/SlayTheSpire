#ifndef GETCARDPIXMAP_H
#define GETCARDPIXMAP_H

#include <QPixmap>
#include "categories/cards.h"
#include "abstractcardtemplate.h"

inline QPixmap getCardPixmap(cardID id)
{
    switch (id)
    {
    // Attack
    case cardID::strike:               return QPixmap(":/image/cards/attack/strike.png");
    case cardID::reaper:               return QPixmap(":/image/cards/attack/reaper.png");
    case cardID::bludgeon:             return QPixmap(":/image/cards/attack/bludgeon.png");
    case cardID::feed:                 return QPixmap(":/image/cards/attack/feed.png");
    case cardID::immolate:             return QPixmap(":/image/cards/attack/immolate.png");
    case cardID::whirlwind:            return QPixmap(":/image/cards/attack/whirlwind.png");
    case cardID::blood_for_blood:      return QPixmap(":/image/cards/attack/blood_for_blood.png");
    case cardID::bash:                 return QPixmap(":/image/cards/attack/bash.png");
    case cardID::twin_strike:          return QPixmap(":/image/cards/attack/twin_strike.png");
    case cardID::perfected_strike:     return QPixmap(":/image/cards/attack/perfected_strike.png");
    case cardID::clash:                return QPixmap(":/image/cards/attack/clash.png");
    case cardID::uppercut:             return QPixmap(":/image/cards/attack/uppercut.png");
    case cardID::heavy_blade:          return QPixmap(":/image/cards/attack/heavy_blade.png");
    case cardID::pommel_strike:        return QPixmap(":/image/cards/attack/pommel_strike.png");
    case cardID::carnage:              return QPixmap(":/image/cards/attack/carnage.png");
    case cardID::hemokinesis:          return QPixmap(":/image/cards/attack/hemokinesis.png");

    // Skill
    case cardID::defend:               return QPixmap(":/image/cards/skill/defend.png");
    case cardID::exhume:               return QPixmap(":/image/cards/skill/exhume.png");
    case cardID::limit_break:          return QPixmap(":/image/cards/skill/limit_break.png");
    case cardID::offering:             return QPixmap(":/image/cards/skill/offering.png");
    case cardID::impervious:           return QPixmap(":/image/cards/skill/impervious.png");
    case cardID::dual_wield:           return QPixmap(":/image/cards/skill/dual_wield.png");
    case cardID::entrench:             return QPixmap(":/image/cards/skill/entrench.png");
    case cardID::warcry:               return QPixmap(":/image/cards/skill/warcry.png");
    case cardID::true_grit:            return QPixmap(":/image/cards/skill/true_grit.png");
    case cardID::shrug_it_off:         return QPixmap(":/image/cards/skill/shrug_it_off.png");
    case cardID::power_through:        return QPixmap(":/image/cards/skill/power_through.png");
    case cardID::bloodletting:         return QPixmap(":/image/cards/skill/bloodletting.png");
    case cardID::disarm:               return QPixmap(":/image/cards/skill/disarm.png");
    case cardID::battle_trance:        return QPixmap(":/image/cards/skill/battle_trance.png");
    case cardID::spot_weakness:        return QPixmap(":/image/cards/skill/spot_weakness.png");
    case cardID::rage:                 return QPixmap(":/image/cards/skill/rage.png");
    case cardID::JAX:                  return QPixmap(":/image/cards/skill/JAX.png");

    // Power
    case cardID::inflame:              return QPixmap(":/image/cards/power/inflame.png");
    case cardID::metallicize:          return QPixmap(":/image/cards/power/metallicize.png");
    case cardID::demon_form:           return QPixmap(":/image/cards/power/demon_form.png");
    case cardID::brutality:            return QPixmap(":/image/cards/power/brutality.png");
    case cardID::feel_no_pain:         return QPixmap(":/image/cards/power/feel_no_pain.png");
    case cardID::barricade:            return QPixmap(":/image/cards/power/barricade.png");
    case cardID::dark_embrace:         return QPixmap(":/image/cards/power/dark_embrace.png");
    case cardID::berserk:              return QPixmap(":/image/cards/power/berserk.png");

    // Status
    case cardID::dazed:                return QPixmap(":/image/cards/status/dazed.png");
    case cardID::slimed:               return QPixmap(":/image/cards/status/slimed.png");
    case cardID::wound:                return QPixmap(":/image/cards/status/wound.png");
    case cardID::burn:                 return QPixmap(":/image/cards/status/burn.png");

    // Curse
    case cardID::curse_of_the_bell:    return QPixmap(":/image/cards/curse/curse_of_bell.png");
    case cardID::regret:               return QPixmap(":/image/cards/curse/regret.png");
    case cardID::writhe:               return QPixmap(":/image/cards/curse/writhe.png");
    case cardID::pain:                 return QPixmap(":/image/cards/curse/pain.png");
    case cardID::shame:                 return QPixmap(":/image/cards/curse/shame.png");
    case cardID::doubt:                 return QPixmap(":/image/cards/curse/doubt.png");
    case cardID::injury:                 return QPixmap(":/image/cards/curse/injury.png");
    }

    return QPixmap();
}

inline QPixmap getCardFrame(CardType id)
{
    switch (id){

    case CardType::attack:              return QPixmap(":/image/card/frame/frame_red.png");
    case CardType::skill:               return QPixmap(":/image/card/frame/frame_green.png");
    case CardType::power:               return QPixmap(":/image/card/frame/frame_purple.png");
    case CardType::status:              return QPixmap(":/image/card/frame/frame_gray.png");
    case CardType::curse:               return QPixmap(":/image/card/frame/frame_black.png");

    }

    return QPixmap();
}

inline QPixmap getBackCard(cardTemplate id) {
    switch (id) {

    case cardTemplate::common: return QPixmap(":/image/cards/back/back.png");
    case cardTemplate::uncommon: return QPixmap(":/image/cards/back/back1.png");
    case cardTemplate::rare: return QPixmap(":/image/cards/back/back2.png");
    case cardTemplate::legend: return QPixmap(":/image/cards/back/back3.png");

    }
    return QPixmap();
}

#endif // GETCARDPIXMAP_H
