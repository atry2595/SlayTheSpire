#ifndef DAZED_H
#define DAZED_H
#include <QObject>
#include "abstractstatuscard.h"

class dazed : public abstractStatusCard
{
    Q_OBJECT

public:

    dazed();
    ~dazed() = default;


    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::dazed; }
    bool is_rare() override { return false; }
};

#endif // DAZED_H
