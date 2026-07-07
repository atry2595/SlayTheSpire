#ifndef SLAVERS_COLLAR_RELIC_H
#define SLAVERS_COLLAR_RELIC_H

#include "abstractrelic.h"

class slavers_collar_relic : public abstractRelic
{
    Q_OBJECT
    bool available = false;
    QMetaObject::Connection combat_start_connection;

public:
    slavers_collar_relic(abstractEntity* owner_init);
    QString generate_description() override;
    relicID get_id() override { return relicID::slavers_collar; }
    relicRarity get_rarity() override { return relicRarity::boss; }


    void added_time(game_action&) override;
    void at_turn_start(game_action&) override;
    void at_combat_end(game_action&) override;
};

#endif // SLAVERS_COLLAR_RELIC_H
