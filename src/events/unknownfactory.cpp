#include "unknownfactory.h"

#include "ominousforge.h"
#include "goldenidol.h"
#include "augmenter.h"
#include "facetrader.h"
#include "bonfirespirits.h"
#include "goldenshrine.h"
#include "lab.h"
#include "thecleric.h"
#include "shininglight.h"
#include "thessssserpent.h"
#include "ancientwriting.h"
#include "joust.h"
#include "pleadingvagrant.h"

UnknownManager unknownFactory::createUnknown(unknownID id, game_action& actions, ironclad* player)
{
    switch (id)
    {
    case unknownID::ominous_forge:    return OminousForge(actions, player).getManager();
    case unknownID::golden_idol:      return GoldenIdol(actions, player).getManager();
    case unknownID::augmenter:        return Augmenter(actions, player).getManager();
    case unknownID::face_trader:      return FaceTrader(actions, player).getManager();
    case unknownID::bonfire_spirits:  return BonfireSpirits(actions, player).getManager();
    case unknownID::golden_shrine:    return GoldenShrine(actions, player).getManager();
    case unknownID::lab:              return Lab(actions, player).getManager();
    case unknownID::the_cleric:       return TheCleric(actions, player).getManager();
    case unknownID::shining_light:    return ShiningLight(actions, player).getManager();
    case unknownID::the_ssssssserpant: return TheSsssserpent(actions, player).getManager();
    case unknownID::ancient_writing:  return AncientWriting(actions, player).getManager();
    case unknownID::the_joust:        return Joust(actions, player).getManager();
    case unknownID::pleading_vagrant: return PleadingVagrant(actions, player).getManager();
    }
}