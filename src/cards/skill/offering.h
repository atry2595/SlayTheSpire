#ifndef OFFERING_H
#define OFFERING_H
#include <QObject>
#include "abstractskillcard.h"

class offering : public abstractSkillCard
{
    Q_OBJECT

protected:
    int base_count = 3;
    int count = 3;

public:

    offering();
    ~offering() = default;

    void combat_reset() override;

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::offering; }
    bool is_rare() override { return true; }

    TargetType get_target_type() override { return TargetType::self; }
};

#endif // OFFERING_H
