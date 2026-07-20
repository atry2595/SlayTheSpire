#ifndef  HAPPY_FLOWER_RELIC_H
#define  HAPPY_FLOWER_RELIC_H

#include "abstractrelic.h"

class happy_flower_relic : public abstractRelic
{
    Q_OBJECT
    int value = 0;

public:
    happy_flower_relic(abstractEntity* owner_init);
    QString generate_description() override;
    relicID get_id() override { return relicID::happy_flower; }
    relicRarity get_rarity() override { return relicRarity::common; }

    void at_turn_start(game_action&) override;
    QString get_story() override;
};

#endif //HAPPY_FLOWER_RELIC_H
