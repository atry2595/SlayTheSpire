#ifndef dark_embrace_H
#define dark_embrace_H
#include <QObject>
#include "abstractpowercard.h"

class dark_embrace : public abstractPowerCard
{
    Q_OBJECT

public:

    dark_embrace();
    ~dark_embrace() = default;

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::dark_embrace; }
    bool is_rare() override { return false; }

    TargetType get_target_type() override { return TargetType::self; }
};

#endif // dark_embrace_H
