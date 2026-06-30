#ifndef HEMOKINESIS_H
#define HEMOKINESIS_H
#include <QObject>
#include "abstractattackcard.h"

class hemokinesis : public abstractAttackCard
{
    Q_OBJECT

    const int dmg = 2;

public:

    hemokinesis();
    ~hemokinesis() = default;

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::hemokinesis; }
};

#endif // HEMOKINESIS_H
