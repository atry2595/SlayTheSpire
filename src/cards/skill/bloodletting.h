#ifndef BLOODLETTING_H
#define BLOODLETTING_H
#include <QObject>
#include "abstractskillcard.h"

class bloodletting : public abstractSkillCard
{
    Q_OBJECT

protected:
    int base_count = 2;
    int count = 2;

public:

    bloodletting();
    ~bloodletting() = default;

    void combat_reset() override;

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::bloodletting; }
    bool is_rare() override { return false; }

    TargetType get_target_type() override { return TargetType::self; }
};

#endif // BLOODLETTING_H
