#ifndef STRIKE_H
#define STRIKE_H
#include <QObject>
#include "abstractattackcard.h"

class strike : public abstractAttackCard
{
    Q_OBJECT

public:
    static constexpr bool is_rare = false;

    strike(bool upgraded_init = false);
    ~strike() = default;

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;
};

#endif // STRIKE_H
