#ifndef GREMLIN_HORN_RELIC_H
#define GREMLIN_HORN_RELIC_H

#include "abstractrelic.h"

class gremlin_horn_relic : public abstractRelic
{
    Q_OBJECT
    QMetaObject::Connection enemy_killed_connection;

public:
    gremlin_horn_relic(abstractEntity* owner_init);
    QString generate_description() override;
    relicID get_id() override { return relicID::gremlin_horn; }
    relicRarity get_rarity() override { return relicRarity::uncommon; }

    void added_time(game_action&) override;
    QString get_story() override;
};

#endif // GREMLIN_HORN_RELIC_H
