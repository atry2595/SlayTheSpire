#ifndef ODDLY_SMOOTH_STONE_RELIC_H
#define ODDLY_SMOOTH_STONE_RELIC_H

#include "abstractrelic.h"

class oddly_smooth_stone_relic : public abstractRelic
{
    Q_OBJECT

public:
    oddly_smooth_stone_relic(abstractEntity* owner_init);
    QString generate_description() override;
    relicID get_id() override { return relicID::oddly_smooth_stone; }
    relicRarity get_rarity() override { return relicRarity::common; }

    void at_combat_start(game_action&) override;
};

#endif // ODDLY_SMOOTH_STONE_RELIC_H
