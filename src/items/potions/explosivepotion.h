#ifndef EXPLOSIVEPOTION_H
#define EXPLOSIVEPOTION_H

#include "abstractpotion.h"

class explosivePotion : public abstractPotion
{
    Q_OBJECT
protected:
    const int amount = 10;
public:
    explosivePotion(abstractEntity* owner);
    void play(playInfo&) override;
    potionID get_ID() override { return potionID::explosive_potion; }
    PotionType get_type() override { return PotionType::common; }
    TargetType get_target_type() override { return TargetType::enemies; }
    QString get_story() override;
};

#endif // EXPLOSIVEPOTION_H
