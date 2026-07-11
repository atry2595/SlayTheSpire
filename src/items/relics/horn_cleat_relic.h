#ifndef HORN_CLEAT_RELIC_H
#define HORN_CLEAT_RELIC_H

#include "abstractrelic.h"

class horn_cleat_relic : public abstractRelic
{
    Q_OBJECT
    int turn = 0;

public:
    horn_cleat_relic(abstractEntity* owner_init);
    QString generate_description() override;
    relicID get_id() override { return relicID::horn_cleat; }
    relicRarity get_rarity() override { return relicRarity::uncommon; }

    void at_turn_start(game_action&) override;
    void at_combat_end(game_action&) override;
};

#endif // HORN_CLEAT_RELIC_H
