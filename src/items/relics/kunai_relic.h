#ifndef KUNAI_RELIC_H
#define KUNAI_RELIC_H

#include "abstractrelic.h"

class kunai_relic : public abstractRelic
{
    Q_OBJECT
    int value = 0;
    QMetaObject::Connection play_card_connection;

public:
    kunai_relic(abstractEntity* owner_init);
    QString generate_description() override;
    relicID get_id() override { return relicID::kunai; }
    relicRarity get_rarity() override { return relicRarity::uncommon; }

    void added_time(game_action&) override;
    void at_turn_start(game_action&) override;
    QString get_story() override;
};

#endif // KUNAI_RELIC_H
