#ifndef FAIRYINABOTTLE_H
#define FAIRYINABOTTLE_H

#include "abstractpotion.h"

class fairyInABottle : public abstractPotion
{
    Q_OBJECT
protected:
    const double amount = 0.3;
    QMetaObject::Connection died_connection;
public:
    fairyInABottle(abstractEntity* owner);
    void play(playInfo&) override;
    void added_time(playInfo&) override;
    potionID get_ID() override { return potionID::fairy_in_a_bottle; }
    PotionType get_type() override { return PotionType::rare; }
    TargetType get_target_type() override { return TargetType::none; }
    bool playable() override { return false; }
};

#endif // FAIRYINABOTTLE_H
