#ifndef FIREPOTION_H
#define FIREPOTION_H

#include "abstractpotion.h"

class firePotion : public abstractPotion
{
    Q_OBJECT

protected:
    const int amount = 20;


public:
    firePotion(abstractEntity* owner);
    void play(playInfo&) override;
    potionID get_ID() override { return potionID::fire_potion; }
    PotionType get_type() override { return PotionType::common; }
    TargetType get_target_type() override { return TargetType::single_target; }
};

#endif // FIREPOTION_H
