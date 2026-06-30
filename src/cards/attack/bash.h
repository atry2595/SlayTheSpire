#ifndef BASH_H
#define BASH_H
#include <QObject>
#include "abstractattackcard.h"

class bash : public abstractAttackCard
{
    Q_OBJECT

protected:

    int base_effect = 2;
    int effect = 2;

public:

    bash();
    ~bash() = default;

    void combat_reset() override;

    int get_effect() { return effect; }

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::bash; }
};

#endif // BASH_H
