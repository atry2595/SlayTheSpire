#ifndef REGRET_H
#define REGRET_H
#include <QObject>
#include "abstractcursecard.h"

class regret : public abstractCurseCard
{
    Q_OBJECT

public:

    regret();
    ~regret() = default;


    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;
    void hand_turn_end(playInfo&) override;

    cardID get_card_id() override { return cardID::regret; }
    bool is_rare() override { return false; }
    bool can_remove_from_deck() override { return true; }
    TargetType get_target_type() override { return TargetType::none; }
};

#endif // REGRET_H
