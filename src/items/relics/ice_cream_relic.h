#ifndef ICE_CREAM_RELIC_H
#define ICE_CREAM_RELIC_H

#include "abstractrelic.h"

class ice_cream_relic : public abstractRelic
{
    Q_OBJECT

public:
    ice_cream_relic(abstractEntity* owner_init);
    ~ice_cream_relic() override;
    QString generate_description() override;
    relicID get_id() override { return relicID::ice_cream; }
    relicRarity get_rarity() override { return relicRarity::rare; }

    void added_time(game_action&) override;
    QString get_story() override;
};

#endif // ICE_CREAM_RELIC_H
