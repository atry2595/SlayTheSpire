#include "ironclad.h"

const std::vector<cardID> ironclad::starting_deck =
    {cardID::strike, cardID::strike, cardID::strike, cardID::strike, cardID::strike,
     cardID::defend, cardID::defend, cardID::defend, cardID::defend, cardID::bash};

ironclad::ironclad()
    :abstractEntity(tr("Ironclad"), 80)
{}
