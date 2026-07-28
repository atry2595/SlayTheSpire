#ifndef CURSED_KEY_RELIC_H
#define CURSED_KEY_RELIC_H

#include "abstractrelic.h"

class cursed_key_relic : public abstractRelic
{
    Q_OBJECT
    QMetaObject::Connection open_chest_connection;

public:
    cursed_key_relic(abstractEntity* owner_init);
    QString generate_description() override;
    relicID get_id() override { return relicID::cursed_key; }
    relicRarity get_rarity() override { return relicRarity::boss; }

    void added_time(game_action&) override;
    QString get_story() override;
};

#endif // CURSED_KEY_RELIC_H
