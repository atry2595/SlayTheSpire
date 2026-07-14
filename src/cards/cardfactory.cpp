#include "cardfactory.h"

// Attack
#include "cards/attack/bash.h"
#include "cards/attack/blood_for_blood.h"
#include "cards/attack/bludgeon.h"
#include "cards/attack/carnage.h"
#include "cards/attack/clash.h"
#include "cards/attack/feed.h"
#include "cards/attack/heavy_blade.h"
#include "cards/attack/hemokinesis.h"
#include "cards/attack/immolate.h"
#include "cards/attack/perfected_strike.h"
#include "cards/attack/pommel_strike.h"
#include "cards/attack/reaper.h"
#include "cards/attack/strike.h"
#include "cards/attack/twin_strike.h"
#include "cards/attack/uppercut.h"
#include "cards/attack/whirlwind.h"

// Curse
#include "cards/curse/curse_of_the_bell.h"
#include "cards/curse/pain.h"
#include "cards/curse/regret.h"
#include "cards/curse/writhe.h"
#include "cards/curse/injury.h"
#include "cards/curse/shame.h"

// Power
#include "cards/power/barricade.h"
#include "cards/power/berserk.h"
#include "cards/power/brutality.h"
#include "cards/power/dark_embrace.h"
#include "cards/power/demon_form.h"
#include "cards/power/feel_no_pain.h"
#include "cards/power/inflame.h"
#include "cards/power/metallicize.h"

// Skill
#include "cards/skill/battle_trance.h"
#include "cards/skill/bloodletting.h"
#include "cards/skill/defend.h"
#include "cards/skill/disarm.h"
#include "cards/skill/dual_wield.h"
#include "cards/skill/entrench.h"
#include "cards/skill/exhume.h"
#include "cards/skill/impervious.h"
#include "cards/skill/jax.h"
#include "cards/skill/limitbreak.h"
#include "cards/skill/offering.h"
#include "cards/skill/power_through.h"
#include "cards/skill/rage.h"
#include "cards/skill/shrug_it_off.h"
#include "cards/skill/spot_weakness.h"
#include "cards/skill/true_grit.h"
#include "cards/skill/warcry.h"

// Status
#include "cards/status/burn.h"
#include "cards/status/dazed.h"
#include "cards/status/slimed.h"
#include "cards/status/wound.h"

abstractCard* CardFactory::createCard(cardID id)
{
    switch (id)
    {
    // Attack
    case cardID::bash: return new bash;
    case cardID::blood_for_blood: return new blood_for_blood;
    case cardID::bludgeon: return new bludgeon;
    case cardID::carnage: return new carnage;
    case cardID::clash: return new clash;
    case cardID::feed: return new feed;
    case cardID::heavy_blade: return new heavy_blade;
    case cardID::hemokinesis: return new hemokinesis;
    case cardID::immolate: return new immolate;
    case cardID::perfected_strike: return new perfected_strike;
    case cardID::pommel_strike: return new pommel_strike;
    case cardID::reaper: return new reaper;
    case cardID::strike: return new strike;
    case cardID::twin_strike: return new twin_strike;
    case cardID::uppercut: return new uppercut;
    case cardID::whirlwind: return new whirlwind;

    // Curse
    case cardID::curse_of_the_bell: return new curse_of_the_bell;
    case cardID::pain: return new pain;
    case cardID::regret: return new regret;
    case cardID::writhe: return new writhe;
    case cardID::injury: return new injury;
    case cardID::shame: return new shame;

    // Power
    case cardID::barricade: return new barricade;
    case cardID::berserk: return new berserk;
    case cardID::brutality: return new brutality;
    case cardID::dark_embrace: return new dark_embrace;
    case cardID::demon_form: return new demon_form;
    case cardID::feel_no_pain: return new feel_no_pain;
    case cardID::inflame: return new inflame;
    case cardID::metallicize: return new metallicize;

    // Skill
    case cardID::battle_trance: return new battle_trance;
    case cardID::bloodletting: return new bloodletting;
    case cardID::defend: return new defend;
    case cardID::disarm: return new disarm;
    case cardID::dual_wield: return new dual_wield;
    case cardID::entrench: return new entrench;
    case cardID::exhume: return new exhume;
    case cardID::impervious: return new impervious;
    case cardID::JAX: return new JAX;
    case cardID::limit_break: return new limit_break;
    case cardID::offering: return new offering;
    case cardID::power_through: return new power_through;
    case cardID::rage: return new rage;
    case cardID::shrug_it_off: return new shrug_it_off;
    case cardID::spot_weakness: return new spot_weakness;
    case cardID::true_grit: return new true_grit;
    case cardID::warcry: return new warcry;

    // Status
    case cardID::burn: return new burn;
    case cardID::dazed: return new dazed;
    case cardID::slimed: return new slimed;
    case cardID::wound: return new wound;

    default:
        return nullptr;
    }
}