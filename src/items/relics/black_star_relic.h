#ifndef BLACK_STAR_RELIC_H
#define BLACK_STAR_RELIC_H

#include "abstractrelic.h"

class black_star_relic : public abstractRelic
{
    Q_OBJECT
    QMetaObject::Connection start_combat_connection;

public:
    black_star_relic(abstractEntity* owner_init);
    QString generate_description() override;
    relicID get_id() override { return relicID::black_star; }
    relicRarity get_rarity() override { return relicRarity::boss; }

    void added_time(game_action&) override;
    QString get_story() override;
};

#endif // BLACK_STAR_RELIC_H
