#ifndef BATTLE_TRANCE_H
#define BATTLE_TRANCE_H
#include <QObject>
#include "abstractskillcard.h"

class battle_trance : public abstractSkillCard
{
    Q_OBJECT

protected:
    int base_count = 3;
    int count = 3;

public:

    battle_trance();
    ~battle_trance() = default;

    void combat_reset() override;

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::battle_trance; }
    bool is_rare() override { return false; }

    TargetType get_target_type() override { return TargetType::self; }
};

#endif // BATTLE_TRANCE_H
