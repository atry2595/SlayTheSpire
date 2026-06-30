#ifndef BLUDGEON_H
#define BLUDGEON_H
#include <QObject>
#include "abstractattackcard.h"

class bludgeon : public abstractAttackCard
{
    Q_OBJECT

public:

    bludgeon();
    ~bludgeon() = default;

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::bludgeon; }
    bool is_rare() override { return true; }
};

#endif // bludgeon_H
