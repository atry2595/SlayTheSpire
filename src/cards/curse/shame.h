#ifndef SHAME_H
#define SHAME_H
#include <QObject>
#include "abstractcursecard.h"

class shame : public abstractCurseCard
{
    Q_OBJECT

public:

    shame();
    ~shame() = default;


    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::shame; }
    bool is_rare() override { return false; }
    bool can_remove_from_deck() override { return true; }
    TargetType get_target_type() override { return TargetType::none; }

    void hand_turn_end(playInfo&) override;
};

#endif // SHAME_H
