#ifndef CARNAGE_H
#define CARNAGE_H
#include <QObject>
#include "abstractattackcard.h"

class carnage : public abstractAttackCard
{
    Q_OBJECT

public:
    static constexpr bool is_rare = false;

    carnage(bool upgraded_init = false);
    ~carnage() = default;

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;
};

#endif // CARNAGE_H
