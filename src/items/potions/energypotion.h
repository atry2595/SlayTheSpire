#ifndef ENERGYPOTION_H
#define ENERGYPOTION_H

#include "abstractpotion.h"

class energyPotion : public abstractPotion
{
    Q_OBJECT
protected:
    const int amount = 2;
public:
    energyPotion(abstractEntity* owner);
    void play(playInfo&) override;
    potionID get_ID() override { return potionID::energy_potion; }
    PotionType get_type() override { return PotionType::common; }
    TargetType get_target_type() override { return TargetType::self; }
};

#endif // ENERGYPOTION_H
