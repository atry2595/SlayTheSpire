#ifndef ENTRENCH_H
#define ENTRENCH_H
#include <QObject>
#include "abstractskillcard.h"

class entrench : public abstractSkillCard
{
    Q_OBJECT


public:

    entrench();
    ~entrench() = default;

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::entrench; }
    bool is_rare() override { return false; }
    TargetType get_target_type() override { return TargetType::self; }
};

#endif // ENTRENCH_H
