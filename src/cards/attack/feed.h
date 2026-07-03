#ifndef FEED_H
#define FEED_H
#include <QObject>
#include "abstractattackcard.h"

class feed : public abstractAttackCard
{
    Q_OBJECT


protected:
    int base_effect = 3;
    int effect = 3;

public:

    feed();
    ~feed() = default;

    void combat_reset() override;

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::feed; }
    bool is_rare() override { return true; }

    TargetType get_target_type() override { return TargetType::single_target; }
};

#endif // FEED_H
