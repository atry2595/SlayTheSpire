#ifndef BURNING_BLOOD_RELIC_H
#define BURNING_BLOOD_RELIC_H

#include "abstractrelic.h"

class burning_blood_relic : public abstractRelic
{
    Q_OBJECT
    const int value = 6;

public:
    burning_blood_relic(abstractEntity* owner_init);
    QString generate_description() override;
    relicID get_id() override { return relicID::burning_blood; }
    relicRarity get_rarity() override { return relicRarity::starter; }

    void at_combat_end(game_action&) override;
};

#endif // BURNING_BLOOD_RELIC_H
