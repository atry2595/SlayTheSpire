#ifndef SWIFTPOTION_H
#define SWIFTPOTION_H

#include "abstractpotion.h"

class swiftPotion : public abstractPotion
{
    Q_OBJECT
protected:
    const int amount = 3;
public:
    swiftPotion(abstractEntity* owner);
    void play(playInfo&) override;
    potionID get_ID() override { return potionID::swift_potion; }
    PotionType get_type() override { return PotionType::common; }
    TargetType get_target_type() override { return TargetType::self; }
    QString get_story() override;
};

#endif // SWIFTPOTION_H
