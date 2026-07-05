#ifndef BRUTALITY_H
#define BRUTALITY_H
#include <QObject>
#include "abstractpowercard.h"

class brutality : public abstractPowerCard
{
    Q_OBJECT

public:

    brutality();
    ~brutality() = default;

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::brutality; }
    bool is_rare() override { return true; }

    TargetType get_target_type() override { return TargetType::self; }
};

#endif // BRUTALITY_H
