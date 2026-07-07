#ifndef GREMLIN_VISAGE_RELIC_H
#define GREMLIN_VISAGE_RELIC_H

#include "abstractrelic.h"

class gremlin_visage_relic : public abstractRelic
{
    Q_OBJECT

public:
    gremlin_visage_relic(abstractEntity* owner_init);
    QString generate_description() override;
    relicID get_id() override { return relicID::gremlin_visage; }
    relicRarity get_rarity() override { return relicRarity::event; }

    void at_combat_start(game_action&) override;
};

#endif // GREMLIN_VISAGE_RELIC_H
