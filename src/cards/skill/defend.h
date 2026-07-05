#ifndef DEFEND_H
#define DEFEND_H
#include <QObject>
#include "abstractskillcard.h"

class defend : public abstractSkillCard
{
    Q_OBJECT

protected:

    int base_effect = 5;
    int effect = 5;

public:

    defend();
    ~defend() = default;

    void combat_reset() override;

    int get_effect() { return effect; }

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::defend; }
    bool is_rare() override { return false; }

    TargetType get_target_type() override { return TargetType::self; }
};

#endif // DEFEND_H
