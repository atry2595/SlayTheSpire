#ifndef BERSERK_H
#define BERSERK_H
#include <QObject>
#include "abstractpowercard.h"

class berserk : public abstractPowerCard
{
    Q_OBJECT

protected:
    int base_effect = 2;
    int effect = 2;

public:

    berserk();
    ~berserk() = default;

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::berserk; }
    bool is_rare() override { return false; }

    TargetType get_target_type() override { return TargetType::self; }
};

#endif // BERSERK_H
