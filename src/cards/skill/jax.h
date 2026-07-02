#ifndef JAX_H
#define JAX_H
#include <QObject>
#include "abstractskillcard.h"

class JAX : public abstractSkillCard
{
    Q_OBJECT

protected:

    int base_effect = 2;
    int effect = 2;
    int base_dmg = 3;
    int dmg = 3;


public:

    JAX();
    ~JAX() = default;

    void combat_reset() override;

    int get_effect() { return effect; }

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::JAX; }
    bool is_rare() override { return false; }

    TargetType get_target_type() override { return TargetType::self; }
};

#endif // JAX_H
