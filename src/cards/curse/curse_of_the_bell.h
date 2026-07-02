#ifndef CURSE_OF_THE_BELL_H
#define CURSE_OF_THE_BELL_H
#include <QObject>
#include "abstractcursecard.h"

class curse_of_the_bell : public abstractCurseCard
{
    Q_OBJECT

public:

    curse_of_the_bell();
    ~curse_of_the_bell() = default;


    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::curse_of_the_bell; }
    bool is_rare() override { return false; }
    bool can_remove_from_deck() override { return false; }
    TargetType get_target_type() override { return TargetType::none; }
};

#endif // CURSE_OF_THE_BELL_H
