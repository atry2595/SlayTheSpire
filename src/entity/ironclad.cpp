#include "ironclad.h"
#include "cards/cardfactory.h"
#include "cards/cardfactory.h"
#include "utils/RNG.h"
#include "items/potions/abstractpotion.h"
#include "categories/general.h"


ironclad::ironclad(combatEvent* eve)
    :abstractEntity(tr("Ironclad"), 80),
    event(eve)
{
    energy = base_energy;

    for (auto item : ironclad::starting_deck){
        abstractCard* nc = CardFactory::createCard(item);
        deck.push_back(nc);
    }
}


