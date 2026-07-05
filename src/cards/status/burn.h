#ifndef BURN_H
#define BURN_H
#include <QObject>
#include "abstractstatuscard.h"

class burn : public abstractStatusCard
{
    Q_OBJECT

protected:
    int base_dmg = 2;
    int dmg = 2;

public:

    burn();
    ~burn() = default;


    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;
    void curse_upgrade();
    void hand_turn_end(playInfo& play_info) override;

    cardID get_card_id() override { return cardID::burn; }
    bool is_rare() override { return false; }

    TargetType get_target_type() override { return TargetType::none; }
};

#endif // BURN_H
