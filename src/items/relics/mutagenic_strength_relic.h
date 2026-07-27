#ifndef MUTAGENI_STRENGTH_RELIC_H
#define MUTAGENI_STRENGTH_RELIC_H

#include "abstractrelic.h"

class mutagenic_strength_relic : public abstractRelic
{
    Q_OBJECT
    bool used = false;

public:
    mutagenic_strength_relic(abstractEntity* owner_init);
    QString generate_description() override;
    relicID get_id() override { return relicID::mutagenic_strength; }
    relicRarity get_rarity() override { return relicRarity::event; }

    void at_combat_start(game_action&) override;
    void at_turn_end(game_action&) override;
    QString get_story() override;
};

#endif // MUTAGENI_STRENGTH_RELIC_H
