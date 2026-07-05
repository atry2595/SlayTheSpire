#ifndef TRUE_GRIT_H
#define TRUE_GRIT_H
#include <QObject>
#include "abstractskillcard.h"

class true_grit : public abstractSkillCard
{
    Q_OBJECT

protected:
    int base_block = 7;
    int block = 7;

    bool random_select = true;
    bool base_random_select = true;

public:

    true_grit();
    ~true_grit() = default;

    void combat_reset() override;

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::true_grit; }
    bool is_rare() override { return false; }

    TargetType get_target_type() override { return TargetType::self; }
};

#endif // TRUE_GRIT_H
