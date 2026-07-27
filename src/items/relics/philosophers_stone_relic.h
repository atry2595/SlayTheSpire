#ifndef PHILOSOPHERS_STONE_RELIC_H
#define PHILOSOPHERS_STONE_RELIC_H

#include "abstractrelic.h"

class philosophers_stone_relic : public abstractRelic
{
    Q_OBJECT
    QMetaObject::Connection game_start_connection;

public:
    philosophers_stone_relic(abstractEntity* owner_init);
    QString generate_description() override;
    relicID get_id() override { return relicID::philosophers_stone; }
    relicRarity get_rarity() override { return relicRarity::boss; }

    void added_time(game_action&) override;
    QString get_story() override;
};

#endif // PHILOSOPHERS_STONE_RELIC_H
