#ifndef GIRYA_RELIC_H
#define GIRYA_RELIC_H

#include "abstractrelic.h"

class girya_relic : public abstractRelic
{
    Q_OBJECT
    int max_value = 3;
    int value = 0;
    QMetaObject::Connection lifting_connection;

public:
    girya_relic(abstractEntity* owner_init);
    QString generate_description() override;
    relicID get_id() override { return relicID::girya; }
    relicRarity get_rarity() override { return relicRarity::rare; }

    void added_time(game_action&) override;
    void at_combat_start(game_action&) override;
};

#endif // GIRYA_RELIC_H
