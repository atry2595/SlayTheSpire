#ifndef IMPERVIOUS_H
#define IMPERVIOUS_H
#include <QObject>
#include "abstractskillcard.h"

class impervious : public abstractSkillCard
{
    Q_OBJECT

protected:

    int base_effect = 30;
    int effect = 30;

public:

    impervious();
    ~impervious() = default;

    void combat_reset() override;

    int get_effect() { return effect; }

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::impervious; }
    bool is_rare() override { return true; }

    TargetType get_target_type() override { return TargetType::self; }
};

#endif // IMPERVIOUS_H
