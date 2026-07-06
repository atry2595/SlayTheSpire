#ifndef DEXTERITYPOTION_H
#define DEXTERITYPOTION_H

#include "abstractpotion.h"

class dexterityPotion : public abstractPotion
{
    Q_OBJECT

protected:
    const int amount = 2;
public:
    dexterityPotion(abstractEntity* owner);
    void play(playInfo&) override;
    potionID get_ID() override { return potionID::dexterity_potion; }
    PotionType get_type() override { return PotionType::common; }
    TargetType get_target_type() override { return TargetType::self; }
};

#endif // DEXTERITYPOTION_H
