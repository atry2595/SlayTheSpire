#include "potionfactory.h"

#include "blockpotion.h"
#include "cultistpotion.h"
#include "dexteritypotion.h"
#include "energypotion.h"
#include "explosivepotion.h"
#include "fairyinabottle.h"
#include "fearpotion.h"
#include "firepotion.h"
#include "strengthpotion.h"
#include "swiftpotion.h"
#include "weakpotion.h"
#include "whitebloodpotion.h"

abstractPotion* PotionFactory::createPotion(potionID id, abstractEntity* owner)
{
    switch (id)
    {
    case potionID::block_potion:
        return new blockPotion(owner);

    case potionID::fire_potion:
        return new firePotion(owner);

    case potionID::energy_potion:
        return new energyPotion(owner);

    case potionID::swift_potion:
        return new swiftPotion(owner);

    case potionID::fairy_in_a_bottle:
        return new fairyInABottle(owner);

    case potionID::dexterity_potion:
        return new dexterityPotion(owner);

    case potionID::explosive_potion:
        return new explosivePotion(owner);

    case potionID::fear_potion:
        return new fearPotion(owner);

    case potionID::strength_potion:
        return new strengthPotion(owner);

    case potionID::weak_potion:
        return new weakPotion(owner);

    case potionID::white_blood_potion:
        return new whiteBloodPotion(owner);

    case potionID::cultist_potion:
        return new cultistPotion(owner);

    default:
        return nullptr;
    }
}