#ifndef GOLDEN_IDOL_RELIC_H
#define GOLDEN_IDOL_RELIC_H

#include "abstractrelic.h"

class golden_idol_relic : public abstractRelic
{
    Q_OBJECT
    QMetaObject::Connection end_combat_connection;

public:
    golden_idol_relic(abstractEntity* owner_init);
    QString generate_description() override;
    relicID get_id() override { return relicID::golden_idol; }
    relicRarity get_rarity() override { return relicRarity::event; }

    void added_time(game_action&) override;
};

#endif // GOLDEN_IDOL_RELIC_H
