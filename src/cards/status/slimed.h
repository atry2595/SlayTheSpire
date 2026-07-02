#ifndef SLIMED_H
#define SLIMED_H
#include <QObject>
#include "abstractstatuscard.h"

class slimed : public abstractStatusCard
{
    Q_OBJECT

public:

    slimed();
    ~slimed() = default;


    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::slimed; }
    bool is_rare() override { return false; }

    TargetType get_target_type() override { return TargetType::single_target; }
};

#endif // SLIMED_H
