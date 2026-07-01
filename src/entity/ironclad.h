#ifndef IRONCLAD_H
#define IRONCLAD_H

#include <QWidget>
#include <vector>
#include "abstractentity.h"
#include "categories/cards.h"
#include "categories/relics.h"

class ironclad : public abstractEntity
{
    Q_OBJECT

protected:

public:
    ironclad();

    entityType get_type() override { return entityType::player; }
    entityID get_ID() override { return entityID::ironclad; }

    static const std::vector<cardID> starting_deck;

    static constexpr relicID starting_relic = relicID::burning_blood;

    static constexpr int starting_gold = 99;
};


#endif // IRONCLAD_H
