#ifndef FEARPOTION_H
#define FEARPOTION_H

#include "abstractpotion.h"

class fearPotion : public abstractPotion
{
    Q_OBJECT

protected:
    const int amount = 3;
public:
    fearPotion(abstractEntity* owner);
    void play(playInfo&) override;
    potionID get_ID() override { return potionID::fear_potion; }
    PotionType get_type() override { return PotionType::common; }
    TargetType get_target_type() override { return TargetType::single_target; }
    QString get_story() override;
};

#endif // FEARPOTION_H
