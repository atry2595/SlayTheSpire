#ifndef BAG_OF_MARBLES_RELIC_H
#define BAG_OF_MARBLES_RELIC_H

#include "abstractrelic.h"

class bag_of_marbles_relic : public abstractRelic
{
    Q_OBJECT
    QMetaObject::Connection start_combat_connection;

public:
    bag_of_marbles_relic(abstractEntity* owner_init);
    QString generate_description() override;
    relicID get_id() override { return relicID::bag_of_marbles; }
    relicRarity get_rarity() override { return relicRarity::common; }

    void added_time(game_action&) override;
};

#endif // BAG_OF_MARBLES_RELIC_H
