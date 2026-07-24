#ifndef CULTIST_HEADPIECE_RELIC_H
#define CULTIST_HEADPIECE_RELIC_H

#include "abstractrelic.h"

class cultist_headpiece_relic : public abstractRelic
{
    Q_OBJECT
    QMetaObject::Connection start_combat_connection;

public:
    cultist_headpiece_relic(abstractEntity* owner_init);
    QString generate_description() override;
    relicID get_id() override { return relicID::cultist_headpiece; }
    relicRarity get_rarity() override { return relicRarity::event; }

    void at_combat_start(game_action&) override;
    QString get_story() override;
};

#endif // CULTIST_HEADPIECE_RELIC_H
