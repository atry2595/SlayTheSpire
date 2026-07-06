#ifndef WEAKPOTION_H
#define WEAKPOTION_H

#include "abstractpotion.h"

class weakPotion : public abstractPotion
{
    Q_OBJECT

protected:
    const int amount = 3;
public:
    weakPotion(abstractEntity* owner);
    void play(playInfo&) override;
    potionID get_ID() override { return potionID::weak_potion; }
    PotionType get_type() override { return PotionType::common; }
    TargetType get_target_type() override { return TargetType::single_target; }
};

#endif // WEAKPOTION_H
