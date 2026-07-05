#ifndef FEEL_NO_PAIN_H
#define FEEL_NO_PAIN_H
#include <QObject>
#include "abstractpowercard.h"

class feel_no_pain : public abstractPowerCard
{
    Q_OBJECT

protected:
    int base_effect = 3;
    int effect = 3;
public:

    feel_no_pain();
    ~feel_no_pain() = default;

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::feel_no_pain; }
    bool is_rare() override { return false; }

    TargetType get_target_type() override { return TargetType::self; }
};

#endif // FEEL_NO_PAIN_H
