#ifndef DISARM_H
#define DISARM_H
#include <QObject>
#include "abstractskillcard.h"

class disarm : public abstractSkillCard
{
    Q_OBJECT

    int base_effect = 2;
    int effect = 2;

public:

    disarm();
    ~disarm() = default;

    int get_effect() { return effect; }

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::disarm; }
    bool is_rare() override { return false; }
};

#endif // DISARM_H
