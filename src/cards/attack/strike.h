#ifndef STRIKE_H
#define STRIKE_H
#include <QObject>
#include "abstractattackcard.h"

class strike : public abstractAttackCard
{
    Q_OBJECT

public:

    strike();
    ~strike() = default;

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::strike; }
    bool is_rare() override { return false; }
};

#endif // STRIKE_H
