#ifndef TUNGSTEN_ROD_RELIC_H
#define TUNGSTEN_ROD_RELIC_H

#include "abstractrelic.h"

class tungsten_rod_relic : public abstractRelic
{
    Q_OBJECT
    QMetaObject::Connection before_damage_connection;

public:
    tungsten_rod_relic(abstractEntity* owner_init);
    QString generate_description() override;
    relicID get_id() override { return relicID::tungsten_rod; }
    relicRarity get_rarity() override { return relicRarity::rare; }

    void added_time(game_action&) override;
    QString get_story() override;
};

#endif // TUNGSTEN_ROD_RELIC_H
