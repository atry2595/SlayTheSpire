#ifndef WRITHE_H
#define WRITHE_H
#include <QObject>
#include "abstractcursecard.h"

class writhe : public abstractCurseCard
{
    Q_OBJECT

public:

    writhe();
    ~writhe() = default;


    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::writhe; }
    bool is_rare() override { return false; }
    bool can_remove_from_deck() override { return false; }
    TargetType get_target_type() override { return TargetType::none; }
};

#endif // WRITHE_H
