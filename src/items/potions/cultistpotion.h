#ifndef CULTISTPOTION_H
#define CULTISTPOTION_H

#include "abstractpotion.h"

class cultistPotion : public abstractPotion
{
    Q_OBJECT

protected:
    const int amount = 1;
public:
    cultistPotion(abstractEntity* owner);
    void play(playInfo&) override;
    potionID get_ID() override { return potionID::cultist_potion; }
    PotionType get_type() override { return PotionType::common; }
    TargetType get_target_type() override { return TargetType::self; }
};

#endif // CULTISTPOTION_H
