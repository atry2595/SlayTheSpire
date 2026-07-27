#ifndef GREENBACK_RELIC_H
#define GREENBACK_RELIC_H

#include "abstractrelic.h"

class greenback_relic : public abstractRelic
{
    Q_OBJECT
    const int value = 6;

public:
    greenback_relic(abstractEntity* owner_init);
    QString generate_description() override;
    relicID get_id() override { return relicID::greenback; }
    relicRarity get_rarity() override { return relicRarity::common; }

    void at_turn_end(game_action&) override;
    QString get_story() override;
};

#endif // GREENBACK_RELIC_H
