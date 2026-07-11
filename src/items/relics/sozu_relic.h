#ifndef SOZU_RELIC_H
#define SOZU_RELIC_H

#include "abstractrelic.h"

class sozu_relic : public abstractRelic
{
    Q_OBJECT

public:
    sozu_relic(abstractEntity* owner_init);
    QString generate_description() override;
    relicID get_id() override { return relicID::sozu; }
    relicRarity get_rarity() override { return relicRarity::boss; }

    void added_time(game_action&) override;
};

#endif // SOZU_RELIC_H
