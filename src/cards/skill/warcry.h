#ifndef WARCRY_H
#define WARCRY_H
#include <QObject>
#include "abstractskillcard.h"

class warcry : public abstractSkillCard
{
    Q_OBJECT

protected:
    int base_count = 1;
    int count = 1;

public:

    warcry();
    ~warcry() = default;

    void combat_reset() override;

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::warcry; }
    bool is_rare() override { return false; }

    TargetType get_target_type() override { return TargetType::self; }
};

#endif // WARCRY_H
