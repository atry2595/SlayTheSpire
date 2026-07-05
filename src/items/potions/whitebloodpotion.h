#ifndef WHITEBLOODPOTION_H
#define WHITEBLOODPOTION_H

#include "abstractpotion.h"

class whiteBloodPotion : public abstractPotion
{
    Q_OBJECT
protected:
    const double amount = 0.2;
public:
    whiteBloodPotion(abstractEntity* owner);
    void play(playInfo&) override;
    potionID get_ID() override { return potionID::white_blood_potion; }
    PotionType get_type() override { return PotionType::uncommon; }
    TargetType get_target_type() override { return TargetType::self; }
};

#endif // WHITEBLOODPOTION_H
