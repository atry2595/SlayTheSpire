#ifndef DEMON_FORM_H
#define DEMON_FORM_H
#include <QObject>
#include "abstractpowercard.h"

class demon_form : public abstractPowerCard
{
    Q_OBJECT

    int base_effect = 2;
    int effect = 2;

public:

    demon_form();
    ~demon_form() = default;

    int get_effect() { return effect; }

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::demon_form; }
    bool is_rare() override { return true; }

    TargetType get_target_type() override { return TargetType::self; }
};

#endif // demon_form_H
