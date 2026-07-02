#ifndef METALLICIZE_H
#define METALLICIZE_H
#include <QObject>
#include "abstractpowercard.h"

class metallicize : public abstractPowerCard
{
    Q_OBJECT

    int base_effect = 3;
    int effect = 3;

public:

    metallicize();
    ~metallicize() = default;

    int get_effect() { return effect; }

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::metallicize; }
    bool is_rare() override { return false; }
    TargetType get_target_type() override { return TargetType::self; }
};

#endif // METALLICIZE_H
