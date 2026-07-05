#ifndef WHIRLWIND_H
#define WHIRLWIND_H
#include <QObject>
#include "abstractattackcard.h"

class whirlwind : public abstractAttackCard
{
    Q_OBJECT


public:

    whirlwind();
    ~whirlwind() = default;

    void combat_reset() override;

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::whirlwind; }
    bool is_rare() override { return false; }
    bool repeat_x_time() override { return true; }
    TargetType get_target_type() override { return TargetType::enemies; }
};

#endif // WHIRLWIND_H
