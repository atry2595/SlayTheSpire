#ifndef LIMITBREAK_H
#define LIMITBREAK_H
#include <QObject>
#include "abstractskillcard.h"

class limit_break : public abstractSkillCard
{
    Q_OBJECT


public:

    limit_break();
    ~limit_break() = default;

    QString generate_description() override;
    void play(playInfo& play_info) override;
    void upgrade() override;
    void base_upgrade() override;

    cardID get_card_id() override { return cardID::limit_break; }
    bool is_rare() override { return true; }
};

#endif // LIMITBREAK_H
