#ifndef MARK_OF_PAIN_RELIC_H
#define MARK_OF_PAIN_RELIC_H

#include "abstractrelic.h"

class mark_of_pain_relic : public abstractRelic
{
    Q_OBJECT

public:
    mark_of_pain_relic(abstractEntity* owner_init);
    QString generate_description() override;
    relicID get_id() override { return relicID::mark_of_pain; }
    relicRarity get_rarity() override { return relicRarity::boss; }

    void added_time(game_action&) override;
    void at_combat_start(game_action&) override;
};

#endif // MARK_OF_PAIN_RELIC_H
