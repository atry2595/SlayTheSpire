#ifndef INJURY_H
#define INJURY_H
#include <QObject>
#include "abstractcursecard.h"

class injury : public abstractCurseCard
{
    Q_OBJECT

public:

    injury();
    ~injury() = default;


    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::injury; }
    bool is_rare() override { return false; }
    bool can_remove_from_deck() override { return true; }
    TargetType get_target_type() override { return TargetType::none; }
};

#endif // INJURY_H
