#ifndef RED_SKULL_RELIC_H
#define RED_SKULL_RELIC_H

#include "abstractrelic.h"

class red_skull_relic : public abstractRelic
{
    Q_OBJECT
    QMetaObject::Connection half_hp_connection;
    bool is_active = false;

public:
    red_skull_relic(abstractEntity* owner_init);
    QString generate_description() override;
    relicID get_id() override { return relicID::red_skull; }
    relicRarity get_rarity() override { return relicRarity::common; }

    void added_time(game_action&) override;
};

#endif // RED_SKULL_RELIC_H
