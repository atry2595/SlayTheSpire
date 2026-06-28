#include "ironclad.h"

ironclad::starting_deck =
    {cards_name::strike, cards_name::strike, cards_name::strike, cards_name::strike, cards_name::strike,
     cards_name::defend, cards_name::defend, cards_name::defend, cards_name::defend, cards_name::bash};

ironclad::ironclad()
    :abstractEntity("Ironclad", 80)
{}
