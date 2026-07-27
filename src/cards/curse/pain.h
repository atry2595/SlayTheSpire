#ifndef PAIN_H
#define PAIN_H
#include <QObject>
#include "abstractcursecard.h"

class pain : public abstractCurseCard
{
    Q_OBJECT

private:
    QMetaObject::Connection play_card_connection;

public:

    pain();
    ~pain() = default;


    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;
    void hand_turn_start(playInfo&) override;
    void hand_turn_end(playInfo&) override;

    cardID get_card_id() override { return cardID::pain; }
    bool is_rare() override { return false; }
    bool can_remove_from_deck() override { return true; }
    TargetType get_target_type() override { return TargetType::none; }
};

#endif // PAIN_H
