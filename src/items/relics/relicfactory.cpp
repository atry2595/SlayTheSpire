#include "relicfactory.h"

#include "burning_blood_relic.h"

#include "girya_relic.h"
#include "ice_cream_relic.h"
#include "shuriken_relic.h"
#include "kunai_relic.h"
#include "anchor_relic.h"
#include "bag_of_marbles_relic.h"
#include "happy_flower_relic.h"
#include "red_skull_relic.h"
#include "preserved_insect_relic.h"
#include "vajra_relic.h"
#include "oddly_smooth_stone_relic.h"
#include "the_boot_relic.h"
#include "greenback_relic.h"
#include "blood_vial_relic.h"
#include "centennial_puzzle_relic.h"
#include "horn_cleat_relic.h"
#include "gremlin_horn_relic.h"
#include "tungsten_rod_relic.h"
#include "captains_wheel_relic.h"

#include "calling_bell_relic.h"
#include "mark_of_pain_relic.h"
#include "velvet_choker_relic.h"
#include "philosophers_stone_relic.h"
#include "slavers_collar_relic.h"
#include "sozu_relic.h"

#include "warped_tongs_relic.h"
#include "mutagenic_strength_relic.h"
#include "red_mask_relic.h"
#include "helmet_of_the_cleric_relic.h"
#include "gremlin_visage_relic.h"
#include "golden_idol_relic.h"

abstractRelic* RelicFactory::createRelic(relicID id, abstractEntity* owner)
{
    switch (id)
    {
    case relicID::burning_blood:
        return new burning_blood_relic(owner);

    case relicID::girya:
        return new girya_relic(owner);
    case relicID::ice_cream:
        return new ice_cream_relic(owner);
    case relicID::shuriken:
        return new shuriken_relic(owner);
    case relicID::kunai:
        return new kunai_relic(owner);
    case relicID::anchor:
        return new anchor_relic(owner);
    case relicID::bag_of_marbles:
        return new bag_of_marbles_relic(owner);
    case relicID::happy_flower:
        return new happy_flower_relic(owner);
    case relicID::red_skull:
        return new red_skull_relic(owner);
    case relicID::preserved_insect:
        return new preserved_insect_relic(owner);
    case relicID::vajra:
        return new vajra_relic(owner);
    case relicID::oddly_smooth_stone:
        return new oddly_smooth_stone_relic(owner);
    case relicID::the_boot:
        return new the_boot_relic(owner);
    case relicID::greenback:
        return new greenback_relic(owner);
    case relicID::blood_vial:
        return new blood_vial_relic(owner);
    case relicID::centennial_puzzle:
        return new centennial_puzzle_relic(owner);
    case relicID::horn_cleat:
        return new horn_cleat_relic(owner);
    case relicID::gremlin_horn:
        return new gremlin_horn_relic(owner);
    case relicID::tungsten_rod:
        return new tungsten_rod_relic(owner);
    case relicID::captains_wheel:
        return new captains_wheel_relic(owner);

    case relicID::calling_bell:
        return new calling_bell_relic(owner);
    case relicID::mark_of_pain:
        return new mark_of_pain_relic(owner);
    case relicID::velvet_choker:
        return new velvet_choker_relic(owner);

    case relicID::black_star:
        return nullptr;

    case relicID::lively_plant:
        return nullptr;

    case relicID::philosophers_stone:
        return new philosophers_stone_relic(owner);

    case relicID::cursed_key:
        return nullptr;

    case relicID::sozu:
        return new sozu_relic(owner);

    case relicID::slavers_collar:
        return new slavers_collar_relic(owner);

    case relicID::warped_tongs:
        return new warped_tongs_relic(owner);
    case relicID::mutagenic_strength:
        return new mutagenic_strength_relic(owner);

    case relicID::cultist_headpiece:
        return nullptr;

    case relicID::red_mask:
        return new red_mask_relic(owner);
    case relicID::helmet_of_cleric:
        return new helmet_of_cleric_relic(owner);
    case relicID::gremlin_visage:
        return new gremlin_visage_relic(owner);
    case relicID::golden_idol:
        return new golden_idol_relic(owner);

    default:
        return nullptr;

    }
}