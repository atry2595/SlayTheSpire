#ifndef TWIN_STRIKE_H
#define TWIN_STRIKE_H
#include <QObject>
#include "abstractattackcard.h"

class twin_strike : public abstractAttackCard
{
    Q_OBJECT

public:
    static constexpr bool is_rare = false;

    twin_strike(bool upgraded_init = false);
    ~twin_strike() = default;

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;
};

#endif // TWIN_STRIKE_H
