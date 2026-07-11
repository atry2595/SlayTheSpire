#ifndef RED_MASK_RELIC_H
#define RED_MASK_RELIC_H

#include "abstractrelic.h"

class red_mask_relic : public abstractRelic
{
    Q_OBJECT
    QMetaObject::Connection start_combat_connection;

public:
    red_mask_relic(abstractEntity* owner_init);
    QString generate_description() override;
    relicID get_id() override { return relicID::red_mask; }
    relicRarity get_rarity() override { return relicRarity::event; }

    void added_time(game_action&) override;
};

#endif // RED_MASK_RELIC_H
