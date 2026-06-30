#ifndef TWIN_STRIKE_H
#define TWIN_STRIKE_H
#include <QObject>
#include "abstractattackcard.h"

class twin_strike : public abstractAttackCard
{
    Q_OBJECT

public:

    twin_strike();
    ~twin_strike() = default;

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::twin_strike; }
};

#endif // TWIN_STRIKE_H
