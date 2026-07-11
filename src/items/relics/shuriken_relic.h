#ifndef SHURIKEN_RELIC_H
#define SHURIKEN_RELIC_H

#include "abstractrelic.h"

class shuriken_relic : public abstractRelic
{
    Q_OBJECT
    int value = 0;
    QMetaObject::Connection play_card_connection;

public:
    shuriken_relic(abstractEntity* owner_init);
    QString generate_description() override;
    relicID get_id() override { return relicID::shuriken; }
    relicRarity get_rarity() override { return relicRarity::uncommon; }

    void added_time(game_action&) override;
    void at_turn_start(game_action&) override;
};

#endif // SHURIKEN_RELIC_H
