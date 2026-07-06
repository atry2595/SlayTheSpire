#ifndef VELVET_CHOKER_RELIC_H
#define VELVET_CHOKER_RELIC_H

#include "abstractrelic.h"

class velvet_choker_relic : public abstractRelic
{
    Q_OBJECT
    int value = 0;
    QMetaObject::Connection play_card_connection;

public:
    velvet_choker_relic(abstractEntity* owner_init);
    QString generate_description() override;
    relicID get_id() override { return relicID::velvet_choker; }
    relicRarity get_rarity() override { return relicRarity::boss; }

    void added_time(game_action&) override;
    void at_turn_start(game_action&) override;
};

#endif // VELVET_CHOKER_RELIC_H
