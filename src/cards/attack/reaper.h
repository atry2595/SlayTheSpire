#ifndef REAPER_H
#define REAPER_H
#include <QObject>
#include "abstractattackcard.h"

class reaper : public abstractAttackCard
{
    Q_OBJECT


public:

    reaper();
    ~reaper() = default;

    void combat_reset() override;

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::reaper; }
    bool is_rare() override { return true; }

    TargetType get_target_type() override { return TargetType::enemies; }
};

#endif // REPAER_H
