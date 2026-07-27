#ifndef ANCHOR_RELIC_H
#define ANCHOR_RELIC_H

#include "abstractrelic.h"

class anchor_relic : public abstractRelic
{
    Q_OBJECT
    const int value = 10;

public:
    anchor_relic(abstractEntity* owner_init);
    QString generate_description() override;
    relicID get_id() override { return relicID::anchor; }
    relicRarity get_rarity() override { return relicRarity::common; }

    void at_combat_start(game_action&) override;
    QString get_story() override;
};

#endif // ANCHOR_RELIC_H
