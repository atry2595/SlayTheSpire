#ifndef THE_BOOT_RELIC_H
#define THE_BOOT_RELIC_H

#include "abstractrelic.h"

class the_boot_relic : public abstractRelic
{
    Q_OBJECT
    int value = 0;
    QMetaObject::Connection before_damage_connection;

public:
    the_boot_relic(abstractEntity* owner_init);
    QString generate_description() override;
    relicID get_id() override { return relicID::the_boot; }
    relicRarity get_rarity() override { return relicRarity::common; }

    void added_time(game_action&) override;
    QString get_story() override;
};

#endif // THE_BOOT_RELIC_H
