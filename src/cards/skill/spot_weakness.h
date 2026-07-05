#ifndef SPOT_WEAKNESS_H
#define SPOT_WEAKNESS_H
#include <QObject>
#include "abstractskillcard.h"

class spot_weakness : public abstractSkillCard
{
    Q_OBJECT


protected:
    int base_effect = 3;
    int effect = 3;

public:

    spot_weakness();
    ~spot_weakness() = default;

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;
    void combat_reset() override;

    cardID get_card_id() override { return cardID::spot_weakness; }
    bool is_rare() override { return false; }

    TargetType get_target_type() override { return TargetType::single_target; }
};

#endif // SPOT_WEAKNESS_H
