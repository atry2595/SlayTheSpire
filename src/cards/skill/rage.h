#ifndef RAGE_H
#define RAGE_H
#include <QObject>
#include "abstractskillcard.h"

class rage : public abstractSkillCard
{
    Q_OBJECT

protected:
    int base_block = 3;
    int block = 3;

public:

    rage();
    ~rage() = default;

    void combat_reset() override;

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::rage; }
    bool is_rare() override { return false; }

    TargetType get_target_type() override { return TargetType::self; }
};

#endif // RAGE_H
