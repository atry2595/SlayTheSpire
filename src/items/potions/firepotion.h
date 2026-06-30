#ifndef FIREPOTION_H
#define FIREPOTION_H

#include "abstractpotion.h"

class firePotion : public abstractPotion
{
    Q_OBJECT
public:
    firePotion(abstractEntity* owner);
    void play(playInfo&) override;
    potionID get_type() override { return potionID::fire_potion; }
};

#endif // FIREPOTION_H
