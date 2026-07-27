#ifndef WARPED_TONGS_RELIC_H
#define WARPED_TONGS_RELIC_H

#include "abstractrelic.h"

class warped_tongs_relic : public abstractRelic
{
    Q_OBJECT

public:
    warped_tongs_relic(abstractEntity* owner_init);
    QString generate_description() override;
    relicID get_id() override { return relicID::warped_tongs; }
    relicRarity get_rarity() override { return relicRarity::event; }

    void at_turn_start(game_action&) override;
    QString get_story() override;
};

#endif // WARPED_TONGS_RELIC_H
