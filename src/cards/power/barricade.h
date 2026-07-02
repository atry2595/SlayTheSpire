#ifndef BARRICADE_H
#define BARRICADE_H
#include <QObject>
#include "abstractpowercard.h"

class barricade : public abstractPowerCard
{
    Q_OBJECT

public:

    barricade();
    ~barricade() = default;


    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::barricade; }
    bool is_rare() override { return true; }

    TargetType get_target_type() override { return TargetType::self; }
};

#endif // BARRICADE_H
