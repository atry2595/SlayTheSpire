#ifndef PRESERVED_INSECT_RELIC_H
#define PRESERVED_INSECT_RELIC_H

#include "abstractrelic.h"

class preserved_insect_relic : public abstractRelic
{
    Q_OBJECT
    QMetaObject::Connection start_combat_connection;

public:
    preserved_insect_relic(abstractEntity* owner_init);
    QString generate_description() override;
    relicID get_id() override { return relicID::preserved_insect; }
    relicRarity get_rarity() override { return relicRarity::common; }

    void added_time(game_action&) override;
    QString get_story() override;
};

#endif // PRESERVED_INSECT_RELIC_H
