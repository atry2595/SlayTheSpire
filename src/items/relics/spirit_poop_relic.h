#ifndef SPIRIT_POOP_RELIC_H
#define SPIRIT_POOP_RELIC_H

#include "abstractrelic.h"

class spirit_poop_relic : public abstractRelic
{
    Q_OBJECT

public:
    spirit_poop_relic(abstractEntity* owner_init);
    QString generate_description() override;
    relicID get_id() override { return relicID::spirit_poop; }
    relicRarity get_rarity() override { return relicRarity::event; }
    QString get_story() override;
};

#endif // SPIRIT_POOP_RELIC_H
