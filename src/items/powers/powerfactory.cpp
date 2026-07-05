#include "powerfactory.h"

#include "barricadepower.h"
#include "berserkpower.h"
#include "brutalitypower.h"
#include "curluppower.h"
#include "darkembracepower.h"
#include "demonformpower.h"
#include "dexteritypower.h"
#include "enragepower.h"
#include "entangledpower.h"
#include "feelnopainpower.h"
#include "frailpower.h"
#include "metallicizePower.h"
#include "painfulstabpower.h"
#include "ragepower.h"
#include "ritualpower.h"
#include "strengthpower.h"
#include "vulnerablePower.h"
#include "weakpower.h"

abstractPower* PowerFactory::createPower(powerID id, abstractEntity* owner, int amount)
{
    switch (id)
    {
    case powerID::barricade:      return new barricadePower(owner, amount);
    case powerID::berserk:        return new berserkPower(owner, amount);
    case powerID::brutality:      return new brutalityPower(owner, amount);
    case powerID::curl_up:        return new curlUpPower(owner, amount);
    case powerID::dark_embrace:   return new darkEmbracePower(owner, amount);
    case powerID::demon_form:     return new demonFormPower(owner, amount);
    case powerID::dexterity:      return new dexterityPower(owner, amount);
    case powerID::enrage:         return new enragePower(owner, amount);
    case powerID::entangled:      return new entangledPower(owner, amount);
    case powerID::feel_no_pain:   return new feelNoPainPower(owner, amount);
    case powerID::frail:          return new frailPower(owner, amount);
    case powerID::metallicize:    return new metallicizePower(owner, amount);
    case powerID::painful_stabs:  return new painfulStabPower(owner, amount);
    case powerID::rage:           return new ragePower(owner, amount);
    case powerID::ritual:         return new ritualPower(owner, amount);
    case powerID::strength:       return new strengthPower(owner, amount);
    case powerID::vulnerable:     return new vulnerablePower(owner, amount);
    case powerID::weak:           return new weakPower(owner, amount);

    default:
        return nullptr;
    }
}