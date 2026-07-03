#ifndef EXHUME_H
#define EXHUME_H
#include <QObject>
#include "abstractskillcard.h"

class exhume : public abstractSkillCard
{
    Q_OBJECT


public:

    exhume();
    ~exhume() = default;

    void combat_reset() override;

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::exhume; }
    bool is_rare() override { return true; }

    TargetType get_target_type() override { return TargetType::self; }
};

#endif // EXHUME_H
