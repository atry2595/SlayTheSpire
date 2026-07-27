#ifndef CENTENNIAL_PUZZLE_RELIC_H
#define CENTENNIAL_PUZZLE_RELIC_H

#include "abstractrelic.h"

class centennial_puzzle_relic : public abstractRelic
{
    Q_OBJECT
    bool active = true;

public:
    centennial_puzzle_relic(abstractEntity* owner_init);
    QString generate_description() override;
    relicID get_id() override { return relicID::centennial_puzzle; }
    relicRarity get_rarity() override { return relicRarity::common; }

    void at_combat_start(game_action&) override;
    void damage_applied(game_action&) override;
    QString get_story() override;
};

#endif // CENTENNIAL_PUZZLE_RELIC_H
