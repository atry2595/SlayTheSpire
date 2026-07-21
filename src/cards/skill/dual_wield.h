#ifndef DUAL_WIELD_H
#define DUAL_WIELD_H
#include <QObject>
#include "abstractskillcard.h"

class dual_wield : public abstractSkillCard
{
    Q_OBJECT

protected:
    int base_count = 1;
    int count = 1;

    QMetaObject::Connection cnt;

public:

    dual_wield();
    ~dual_wield() = default;

    void combat_reset() override;

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::dual_wield; }
    bool is_rare() override { return false; }

    TargetType get_target_type() override { return TargetType::self; }
};

#endif // DUAL_WIELD_H
