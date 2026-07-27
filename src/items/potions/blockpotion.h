#ifndef BLOCKPOTION_H
#define BLOCKPOTION_H

#include "abstractpotion.h"

class blockPotion : public abstractPotion
{
    Q_OBJECT

protected:
    const int amount = 12;

public:
    blockPotion(abstractEntity* owner);
    void play(playInfo&) override;
    potionID get_ID() override { return potionID::block_potion; }
    PotionType get_type() override { return PotionType::common; }
    TargetType get_target_type() override { return TargetType::self; }
    QString get_story() override;


};

#endif // BLOCKPOTION_H
