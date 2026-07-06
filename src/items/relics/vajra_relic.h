#ifndef VAJRA_RELIC_H
#define VAJRA_RELIC_H

#include "abstractrelic.h"

class vajra_relic : public abstractRelic
{
    Q_OBJECT

public:
    vajra_relic(abstractEntity* owner_init);
    QString generate_description() override;
    relicID get_id() override { return relicID::vajra; }
    relicRarity get_rarity() override { return relicRarity::common; }

    void at_combat_start(game_action&) override;
};

#endif // VAJRA_RELIC_H
