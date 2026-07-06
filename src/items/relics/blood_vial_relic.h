#ifndef BLOOD_VIAL_RELIC_H
#define BLOOD_VIAL_RELIC_H

#include "abstractrelic.h"

class blood_vial_relic : public abstractRelic
{
    Q_OBJECT

public:
    blood_vial_relic(abstractEntity* owner_init);
    QString generate_description() override;
    relicID get_id() override { return relicID::blood_vial; }
    relicRarity get_rarity() override { return relicRarity::common; }

    void at_combat_start(game_action&) override;
};

#endif // BLOOD_VIAL_RELIC_H
