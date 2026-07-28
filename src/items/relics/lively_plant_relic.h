#ifndef LIVELY_PLANT_RELIC_H
#define LIVELY_PLANT_RELIC_H

#include "abstractrelic.h"

class lively_plant_relic : public abstractRelic
{
    Q_OBJECT

public:
    lively_plant_relic(abstractEntity* owner_init);
    QString generate_description() override;
    relicID get_id() override { return relicID::lively_plant; }
    relicRarity get_rarity() override { return relicRarity::boss; }

    void added_time(game_action&) override;
    QString get_story() override;
};

#endif // LIVELY_PLANT_RELIC_H
