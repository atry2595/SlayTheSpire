#ifndef BLUDGEON_H
#define BLUDGEON_H
#include <QObject>
#include "abstractattackcard.h"

class bludgeon : public abstractAttackCard
{
    Q_OBJECT

public:
    static constexpr bool is_rare = true;

    bludgeon(bool upgraded_init = false);
    ~bludgeon() = default;

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;
};

#endif // bludgeon_H
