#ifndef STRENGTHPOTION_H
#define STRENGTHPOTION_H

#include "abstractpotion.h"

class strengthPotion : public abstractPotion
{
    Q_OBJECT

protected:
    const int amount = 2;
public:
    strengthPotion(abstractEntity* owner);
    void play(playInfo&) override;
    potionID get_ID() override { return potionID::strength_potion; }
    PotionType get_type() override { return PotionType::common; }
    TargetType get_target_type() override { return TargetType::self; }
    QString get_story() override;
};

#endif // STRENGTHPOTION_H
