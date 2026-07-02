#include "cardfactory.h"

#include "cards/attack/bash.h"
#include "cards/attack/bludgeon.h"
#include "cards/attack/carnage.h"
#include "cards/attack/hemokinesis.h"
#include "cards/attack/strike.h"
#include "cards/attack/twin_strike.h"
#include "cards/attack/uppercut.h"

#include "cards/curse/curse_of_the_bell.h"

#include "cards/power/barricade.h"
#include "cards/power/demon_form.h"
#include "cards/power/inflame.h"
#include "cards/power/metallicize.h"

#include "cards/skill/defend.h"
#include "cards/skill/disarm.h"
#include "cards/skill/entrench.h"
#include "cards/skill/impervious.h"
#include "cards/skill/jax.h"
#include "cards/skill/limitbreak.h"

#include "cards/status/dazed.h"
#include "cards/status/slimed.h"
#include "cards/status/wound.h"

abstractCard* CardFactory::createCard(cardID id){
    switch(id){
    case (cardID::strike): return new strike;
    case (cardID::bash): return new bash;
    case (cardID::bludgeon): return new bludgeon;
    case (cardID::carnage): return new carnage;
    case (cardID::hemokinesis): return new hemokinesis;
    case (cardID::twin_strike): return new twin_strike;
    case (cardID::uppercut): return new uppercut;

    case (cardID::curse_of_the_bell): return new curse_of_the_bell;

    case (cardID::barricade): return new barricade;
    case (cardID::demon_form): return new demon_form;
    case (cardID::inflame): return new inflame;
    case (cardID::metallicize): return new metallicize;

    case (cardID::defend): return new defend;
    case (cardID::disarm): return new disarm;
    case (cardID::entrench): return new entrench;
    case (cardID::impervious): return new impervious;
    case (cardID::JAX): return new JAX;
    case (cardID::limit_break): return new limit_break;

    case (cardID::dazed): return new dazed;
    case (cardID::slimed): return new slimed;
    case (cardID::wound): return new wound;

    default: return nullptr;
    }
}