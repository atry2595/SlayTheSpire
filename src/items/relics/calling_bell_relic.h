#ifndef CALLING_BELL_RELIC_H
#define CALLING_BELL_RELIC_H

#include "abstractrelic.h"

class calling_bell_relic : public abstractRelic
{
    Q_OBJECT

public:
    calling_bell_relic(abstractEntity* owner_init);
    QString generate_description() override;
    relicID get_id() override { return relicID::calling_bell; }
    relicRarity get_rarity() override { return relicRarity::boss; }

    void added_time(game_action&) override;
};

#endif // CALLING_BELL_RELIC_H
