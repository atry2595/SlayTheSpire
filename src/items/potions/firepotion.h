#ifndef FIREPOTION_H
#define FIREPOTION_H

#include "abstractpotion.h"

class firePotion : public abstractPotion
{
    Q_OBJECT
public:
    firePotion(abstractEntity* owner);
    void play(playInfo&) override;
    potionID get_ID() override { return potionID::fire_potion; }
    TargetType get_target_type() override { return TargetType::single_target; }
};

#endif // FIREPOTION_H
