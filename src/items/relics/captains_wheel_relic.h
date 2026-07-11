#ifndef CAPTAINS_WHEEL_RELIC_H
#define CAPTAINS_WHEEL_RELIC_H

#include "abstractrelic.h"

class captains_wheel_relic : public abstractRelic
{
    Q_OBJECT
    int turn = 0;

public:
    captains_wheel_relic(abstractEntity* owner_init);
    QString generate_description() override;
    relicID get_id() override { return relicID::captains_wheel; }
    relicRarity get_rarity() override { return relicRarity::rare; }

    void at_turn_start(game_action&) override;
    void at_combat_end(game_action&) override;
};

#endif // CAPTAINS_WHEEL_RELIC_H
