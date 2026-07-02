#ifndef INFLAME_H
#define INFLAME_H
#include <QObject>
#include "abstractpowercard.h"

class inflame : public abstractPowerCard
{
    Q_OBJECT

    int base_effect = 2;
    int effect = 2;

public:

    inflame();
    ~inflame() = default;

    int get_effect() { return effect; }

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::inflame; }
    bool is_rare() override { return false; }
    TargetType get_target_type() override { return TargetType::self; }
    TargetType get_target_type() override { return TargetType::self; }
};

#endif // INFLAME_H
