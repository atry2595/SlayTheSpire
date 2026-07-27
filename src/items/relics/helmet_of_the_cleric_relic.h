#ifndef HELMET_of_CLERIC_RELIC_H
#define HELMET_of_CLERIC_RELIC_H

#include "abstractrelic.h"

class helmet_of_cleric_relic : public abstractRelic
{
    Q_OBJECT

public:
    helmet_of_cleric_relic(abstractEntity* owner_init);
    QString generate_description() override;
    relicID get_id() override { return relicID::helmet_of_the_cleric; }
    relicRarity get_rarity() override { return relicRarity::event; }

    void at_combat_end(game_action&) override;
    QString get_story() override;
};

#endif // HELMET_of_CLERIC_RELIC_H
