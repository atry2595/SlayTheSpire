#ifndef CARNAGE_H
#define CARNAGE_H
#include <QObject>
#include "abstractattackcard.h"

class carnage : public abstractAttackCard
{
    Q_OBJECT

public:

    carnage();
    ~carnage() = default;

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::carnage; }
};

#endif // CARNAGE_H
