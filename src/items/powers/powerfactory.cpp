#include "powerfactory.h"

abstractPower* powerFactory::createPower(powerID id, abstractEntity* owner, int amount){
    switch(id){
    case(powerID::dexterity): return (new dexterityPower(owner, amount));
    case(powerID::frail): return (new frailPower(owner, amount));
    case(powerID::metallicize): return (new metallicizePower(owner, amount));
    case(powerID::ritual): return (new ritualPower(owner, amount));
    case(powerID::strength): return (new strengthPower(owner, amount));
    case(powerID::vulnerable): return (new vulnerablePower(owner, amount));
    case(powerID::weak): return (new weakPower(owner, amount));

    default: return nullptr;
    }
}
